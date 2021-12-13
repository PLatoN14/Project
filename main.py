import pandas as pd
import time
import matplotlib.pyplot as plt
from flask import Flask, render_template, send_file, request

app = Flask(__name__)

df = pd.read_csv("data/city_temperature.csv")
df['Region'] = df['Region'].astype(str)
df['Country'] = df['Country'].astype(str)
df['City'] = df['City'].astype(str)
df['Month'] = df['Month'].astype(int)
df['Day'] = df['Day'].astype(int)
df['Year'] = df['Year'].astype(int)
df['AvgTemperature'] = df['AvgTemperature'].astype(float)

links = {"Download data file (.csv)": "/download_data",
         "View Raw Data": "/view_data",
         "Num_Field": '/num_f',
         "Region": "/region",
         "Country": "/country",
         "City": "/city",
         "Month": "/month",
         "Day": "/day",
         "Year": "/year",
         "AvgTemperature": "/avgTemperature",
         "Analysis_text": "/analysis_text"}

def render_index(image=None, html_string=None, filters=None, current_filter_value="", errors=[]):
    return render_template("index.html", links=links, image=image, code=time.time(), html_string=html_string, filters=filters, current_filter_value = current_filter_value, errors=errors)


@app.route('/', methods=['GET'])
def main_page():
    return render_index()


@app.route(links["Download data file (.csv)"], methods=['GET'])
def download_data():
    return send_file("data/city_temperature.csv", as_attachment=True)

@app.route(links["View Raw Data"], methods=['GET', 'POST'])
def view_data():
    df = pd.read_csv("data/city_temperature.csv")
    html_string = df.to_html()
    return render_index(html_string=html_string)

@app.route(links["Num_Field"], methods=['GET', 'POST'])
def num_f():
    des = df.describe()
    drop_list = ['25%', "max", "75%", "min", "count"]
    for i in drop_list:
        des = des.drop(i)
    des = des.reindex(["mean", "50%", "std"])
    des.index = ["mean", "median", "standard deviation"]
    html_string = des.to_html()
    return render_index(html_string=html_string)

@app.route(links["AvgTemperature"], methods=['GET'])
def average_closing_price():
    plt.figure(num=None, figsize=(12, 6), dpi=100, facecolor='w', edgecolor='k')
    plt.plot(df.groupby('Year')['AvgTemperature'].mean())
    plt.title('AvgTemperature')
    plt.xlabel('Year')
    plt.ylabel('Day')
    plt.savefig('static/tmp/avgTemperature.png')
    return render_index(("avgTemperature.png", "AvgTemperature"))

@app.route(links["AvaTemperature_Per_year"], methods=['GET', 'POST'])
def year_high_low():
    df = pd.read_csv("data/city_temperature.csv")

    fig, ax = plt.subplots(figsize=(12, 8))

    ax.plot(df.groupby('Year')['AvgTemperature'].mean(), label="Year")

    ax.legend(loc=2)
    ax.set_xlabel('Year')
    ax.set_ylabel('AvgTemperature')
    ax.set_title('Avg_per_year')
    plt.savefig('static/tmp/Avg_per_year.png')
    return render_index(("Avg_per_year.png", "Avg_per_year"))

@app.route(links["Analysis"], methods=['GET'])
def download_analysis():
    return render_index(("analysis_text.png", "Analysis_text"))


if __name__ == '__main__':
    app.run()