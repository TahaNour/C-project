from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html', result="")

@app.route('/process_url', methods=['POST'])
def process_url():
    option = request.form.get('option')
    url = request.form.get('url')
    result = ""

    try:
        # Appeler App_c.exe avec les arguments
        process = subprocess.Popen(
            ["./URL_Shortener.exe", option, url],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        stdout, stderr = process.communicate()

        if process.returncode == 0:
            # Traiter et nettoyer la sortie
            result = stdout.decode().strip()
        else:
            result = f"Erreur : {stderr.decode().strip()}"
    except Exception as e:
        result = f"Erreur interne : {e}"

    return render_template('index.html', result=result)

if __name__ == '__main__':
    app.run(debug=True)