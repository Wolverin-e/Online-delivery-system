# python email-test.py abc@bcd.com '1,shampoo,20,30|2,beta,60,44,20|1,shampoo,20,30|2,beta,60,44,20|1,shampoo,20,30|2,beta,60,44,20|1,shampoo,20,30|2,beta,60,44,20'
import sys
import os
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

a = sys.argv[1:]
send_to = a[0]
uname = os.environ.get("my_username")
passwd = os.environ.get("my_password")

email_content = """
<head>
  <style>
    @font-face {
      font-family: 'Poppins';
      font-style: normal;
      font-weight: 400;
      font-display: swap;
      src: local('Poppins Regular'), local('Poppins-Regular'), url(https://fonts.gstatic.com/s/poppins/v9/pxiEyp8kv8JHgFVrJJbecnFHGPezSQ.woff2) format('woff2');
    }
    table{
      border-style: hidden;
      border-collapse: collapse;
      width: 75%;
      font-family: 'Poppins', sans-serif;
    }
    th{
      font-weight: 500;
      text-align: center;
      background: #FFDEAD;
      padding: 0.30%;
    }
    tr{
      text-align: center;
      background: #FFF8DC;
    }
    tr:hover {
      background: #FFEFD5;
    }
    </style>
</head>
<body>
<table style="border:2px;">
  <tr>
    <th>ITEM-ID</th>
    <th>PRODUCT</th>
    <th>PRICE</th>
    <th>QUANTITY</th>
  </tr>
"""
table_template = """
  <tr>
    <td>{}</td>
    <td>{}</td>
    <td>Rs.{}</td>
    <td>{}</td>
  </tr>
"""

net_price = 0
for item_ordered in a[1].split('|'):
  order_details = item_ordered.split(',')
  email_content += table_template.format(order_details[0], order_details[1].upper(), order_details[2], order_details[3])
  net_price += int(order_details[3])*int(order_details[2])


email_content += """
  <tr>
    <th colspan="4">Rs.{}</th>
  </tr>
  </body>
</table>
""".format(net_price)
print(email_content)

MESSAGE = MIMEMultipart('alternative')
MESSAGE['subject'] = "ORDER RECEIPT"
MESSAGE['To'] = send_to
MESSAGE['From'] = uname
HTML_BODY = MIMEText(email_content, 'html')
MESSAGE.attach(HTML_BODY)


server = smtplib.SMTP(host='smtp.gmail.com', port=587)
server.ehlo()
server.starttls()
server.login(uname, passwd)

server.sendmail(uname, send_to, MESSAGE.as_string())

server.quit()