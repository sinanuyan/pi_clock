from flask import Flask, render_template, request


app = Flask(__name__)

@app.route('/')
def index():
    hour_ten_value = 0
    return render_template('index_test.html')

@app.route('/button-click', methods=['POST'])
def button_click():
    data = request.json
    print(data)
    return "button pressed"

if __name__ == '__main__':
    app.run(debug=True)
