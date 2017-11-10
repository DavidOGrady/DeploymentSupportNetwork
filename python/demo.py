#!/usr/bin/python

from pymongo import MongoClient
from pprint import pprint
import cgitb

cgitb.enable()
print("Content-Type: text/html\r\n\r\n")

print("<html><body>")

client = MongoClient("localhost",27017)
db = client.ogrady

collection = db.testData

data = { "id":"mode2", "value":88 }
id = collection.insert_one(data).inserted_id
print("Inserted id: ")
print(id)

for doc in collection.find({}):
   print("<p>")
   print(doc)
   print("</p>")

print("</body></html>")

