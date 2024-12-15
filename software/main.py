from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html')

@app.route('/button-click', methods=['POST'])
def button_click():
    data = request.json
    print(data)
    return "data received"
    