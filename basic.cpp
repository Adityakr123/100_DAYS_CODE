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
h
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


from pyspark.sql import SparkSession
from pyspark.sql.functions import col, when
import pandas as pd
from sqlalchemy import create_engine

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
# Reads line by line
rdd = spark.sparkContext.textFile("hdfs://namenode:8020/user/data/input/*.txt")

# Each line looks like => "ID    AMOUNT+"
split_rdd = rdd.map(lambda line: (line[:12].strip(), line[12:].strip()))  # left part = id, right part = amount+/-  

# Convert to DataFrame
df = split_rdd.toDF(["id", "raw_amount"])

# Add columns: numeric amount and type
df = df.withColumn("amount", col("raw_amount").substr(1, col("raw_amount").length() - 1).cast("double"))
df = df.withColumn("type", when(col("raw_amount").endswith("+"), "CREDIT").otherwise("DEBIT"))

print("Schema from HDFS TXT:")
df.printSchema()
df.show(10, truncate=False)

# ----------------------------
# 3. Convert Spark → Pandas
# ----------------------------
pandas_df = df.select("id", "amount", "type").toPandas()

# ----------------------------
# 4. Insert into Oracle (via pyodbc + SQLAlchemy)
# ----------------------------
username = "ftwoahm"
password = "your_password"
host = "10.191.216.58"
port = "1522"
service_name = "crsprod"

# ODBC DSN string
dsn = f"(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST={host})(PORT={port}))(CONNECT_DATA=(SERVICE_NAME={service_name})))"

# Create SQLAlchemy engine with Oracle ODBC driver
engine = create_engine(f"oracle+pyodbc://{username}:{password}@{dsn}?driver=Oracle%20ODBC%20Driver")

# Insert into existing table
pandas_df.to_sql(
    "your_table_name",  # 🔹 replace with your actual table
    con=engine,
    if_exists="append",  # only append rows
    index=False
)

print("✅ Data inserted into Oracle successfully!")

# ----------------------------
# 5. Stop Spark session
# ----------------------------
spark.stop()



from pyspark.sql import SparkSession
from pyspark.sql.functions import col, when
import pandas as pd
import pyodbc

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
# Reads line by line from HDFS
rdd = spark.sparkContext.textFile("hdfs://namenode:8020/user/data/input/*.txt")

# Assuming fixed-width: left part = id, right part = amount(+/-)
split_rdd = rdd.map(lambda line: (line[:12].strip(), line[12:].strip()))

# Convert to DataFrame
df = split_rdd.toDF(["id", "raw_amount"])

# Add numeric amount + transaction type
df = df.withColumn("amount", col("raw_amount").substr(1, col("raw_amount").length() - 1).cast("double"))
df = df.withColumn("type", when(col("raw_amount").endswith("+"), "CREDIT").otherwise("DEBIT"))

print("Schema from HDFS TXT:")
df.printSchema()
df.show(10, truncate=False)

# ----------------------------
# 3. Convert Spark → Pandas
# ----------------------------
pandas_df = df.select("id", "amount", "type").toPandas()

# ----------------------------
# 4. Insert into Oracle (pyodbc)
# ----------------------------
username = "ftwoahm"
password = "your_password"   # 🔹 replace
host = "10.191.216.58"
port = "1522"
service_name = "crsprod"

# Build DSN string
dsn = f"(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST={host})(PORT={port}))(CONNECT_DATA=(SERVICE_NAME={service_name})))"

# Connect using Oracle ODBC Driver
conn = pyodbc.connect(
    f"DRIVER={{Oracle ODBC Driver}};DBQ={dsn};UID={username};PWD={password}"
)
cursor = conn.cursor()

# Insert rows from pandas DataFrame
for _, row in pandas_df.iterrows():
    cursor.execute(
        "INSERT INTO your_table_name (id, amount, type) VALUES (?, ?, ?)",
        (row["id"], float(row["amount"]), row["type"])
    )

conn.commit()
cursor.close()
conn.close()

print("✅ TXT data processed and loaded into Oracle successfully!")

# ----------------------------
# 5. Stop Spark session
# ----------------------------
spark.stop()







from pyspark.sql import SparkSession
import cx_Oracle
import pandas as pd

# ----------------------------
# 1. Start Spark session
# ----------------------------
spark = SparkSession.builder \
    .appName("HDFS_TXT_to_Oracle_InsertOnly") \
    .config("spark.hadoop.fs.defaultFS", "hdfs://namenode:8020") \
    .getOrCreate()

# ----------------------------
# 2. Read TXT file(s) from HDFS
# ----------------------------
rdd = spark.sparkContext.textFile("hdfs://namenode:8020/user/data/input/*.txt")

# Parse each line → (id, amount, type)
def parse_line(line):
    parts = line.strip()
    record_id = parts[:15]                  # first 15 chars → ID
    raw_amount = parts[15:-1].lstrip("0")   # middle → amount (remove leading zeros)
    sign = parts[-1]                        # last char → '+' or '-'

    if raw_amount == "":
        raw_amount = "0"

    amount = float(raw_amount)
    if sign == "-":
        amount = -amount

    type_val = "POS" if sign == "+" else "NEG"

    return (record_id, amount, type_val)

parsed_rdd = rdd.map(parse_line)

# Convert to DataFrame
df = parsed_rdd.toDF(["id", "amount", "type"])

print("\n===== Parsed Data =====")
df.show(10, truncate=False)

# ----------------------------
# 3. Insert into existing Oracle table
# ----------------------------
pandas_df = df.toPandas()

# Replace with your Oracle connection
conn = cx_Oracle.connect("user", "password", "host:1521/service")
cursor = conn.cursor()

# Insert rows into existing table "transactions"
for _, row in pandas_df.iterrows():
    cursor.execute(
        "INSERT INTO transactions (id, amount, type) VALUES (:1, :2, :3)",
        (row["id"], row["amount"], row["type"])
    )

conn.commit()
cursor.close()
conn.close()

print("\n✅ TXT data inserted into Oracle successfully!")

# ----------------------------
# 4. Stop Spark session
# ----------------------------
spark.stop()


