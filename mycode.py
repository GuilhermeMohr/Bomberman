import flask as f
import numpy as np
import cv2
from markupsafe import escape

app = f.Flask(__name__)

#https://guilhermemohr.github.io/
@app.route('/')
def home():
    return f.render_template('home.html')

@app.route('/projetos')
def projects():
    return f.render_template('project.html', items=items, np=np, cv=cv2)

#@app.route('/projetos/<project>')
#def project(project):
#    return f.render_template('item.html', projetc=project)

items = np.array([
        ('Jogos de Console', 'Cobrinha', 'https://github.com/GuilhermeMohr/Cobrinha', 'C++', 'Jogo', 'images/Cobrinha_print.png'),
        ('Jogos de Console', 'Campo Minado', 'https://github.com/GuilhermeMohr/CampoMinado', 'python', 'Jogo', 'images/CampoMinado_print.png'),
        ('Jogos de Console', 'Bomberman', 'https://github.com/GuilhermeMohr/bomberman', 'C++', 'Jogo', 'images/Bomberman_print.png'),
        ('Jogos de Console', 'Bomberman', 'https://github.com/GuilhermeMohr/bomberman', 'C++', 'Jogo', 'images/Bomberman_print.png'),
        ('Jogos de Console', 'Bomberman', 'https://github.com/GuilhermeMohr/bomberman', 'C++', 'Jogo', 'images/Bomberman_print.png'),
        ('Jogos de Console', 'Bomberman', 'https://github.com/GuilhermeMohr/bomberman', 'C++', 'Jogo', 'images/Bomberman_print.png'),
        ('Jogos de Console', 'Bomberman', 'https://github.com/GuilhermeMohr/bomberman', 'C++', 'Jogo', 'images/Bomberman_print.png'),
        ('Jogos gráficos', 'Pilares de --', 'https://github.com/GuilhermeMohr/C-Godot', 'C# e GDScript', 'Jogo', 'images/Pilares_print.png'),
        ('Jogos gráficos', 'Pilares de --', 'https://github.com/GuilhermeMohr/C-Godot', 'C# e GDScript', 'Jogo', 'images/Pilares_print.png')
    ],
    dtype=[('Grupo', 'U30'), ('Nome', 'U20'), ('Link', 'U50'), ('Linguagem', 'U10'), ('Tipo', 'U10'), ('Imagem', 'U30')])

if __name__ == "__main__":
    app.run(debug=True)
