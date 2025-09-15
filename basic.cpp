from pyspark.sql import SparkSession
import pandas as pd
import cx_Oracle   # for Oracle DB; change to pyodbc if SQL Server

# ----------------------------
# 1. Start Spark session
# ----------------------------
spark = SparkSession.builder \
    .appName("HDFS_Text_to_Oracle") \
    .config("spark.hadoop.fs.defaultFS", "hdfs://namenode:8020") \
    .getOrCreate()

# ----------------------------
# 2. Read TXT file(s) from HDFS
# ----------------------------
# Reads line by line (all *.txt files in folder)
rdd = spark.sparkContext.textFile("hdfs://namenode:8020/user/data/input/*.txt")

# Print ALL file entries (⚠️ careful if very large)
print("\n===== All file entries from HDFS =====")
for line in rdd.collect():
    print(line)

# Example: assume each line looks like => "id,category,amount"
split_rdd = rdd.map(lambda line: line.split(","))

# Convert to DataFrame with schema
df = split_rdd.toDF(["id", "category", "amount"])

print("\n===== Schema from HDFS TXT =====")
df.printSchema()
df.show(5)

# ----------------------------
# 3. Do analytics
# ----------------------------
# Example: average amount per category
df = df.withColumn("amount", df["amount"].cast("double"))
agg_df = df.groupBy("category").avg("amount")

print("\n===== Aggregated results =====")
agg_df.show()

# Convert Spark DataFrame → Pandas for DB insert
pandas_df = agg_df.toPandas()

# ----------------------------
# 4. Insert into Oracle
# ----------------------------
# Adjust with your Oracle credentials + connection details
conn = cx_Oracle.connect("user", "password", "host:1521/service")
cursor = conn.cursor()

# Example: create table if not exists
cursor.execute("""
BEGIN
   EXECUTE IMMEDIATE 'CREATE TABLE category_avg_amount (
       category VARCHAR2(100),
       avg_amount NUMBER
   )';
EXCEPTION
   WHEN OTHERS THEN
      IF SQLCODE != -955 THEN RAISE; END IF;
END;
""")

# Insert rows into Oracle
for _, row in pandas_df.iterrows():
    cursor.execute(
        "INSERT INTO category_avg_amount (category, avg_amount) VALUES (:1, :2)",
        (row["category"], float(row["avg(amount)"]))
    )

conn.commit()
cursor.close()
conn.close()

print("\n✅ TXT data processed and loaded into Oracle successfully!")

# ----------------------------
# 5. Stop Spark session
# ----------------------------
spark.stop()

