#include <GL/glut.h>

// Dimensões da janela
const int WIDTH = 800;
const int HEIGHT = 600;

// Cor das paredes
GLfloat wallColor[] = { 0.78f, 0.69f, 0.58f };

// Cor do chão
GLfloat floorColor[] = { 0.44f,0.5f,0.56f};

// Função para inicializar a cena
void init() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Cor de fundo da janela
    glEnable(GL_DEPTH_TEST); // Habilitar teste de profundidade
}

// Função para desenhar um quadro na parede com moldura
void drawFrame(float x, float y, float z, bool isGoldenFrame = false) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(1.0f, 0.75f, 0.1f); // Dimensões do quadro
    if (isGoldenFrame) {
        glColor3f(1.0f, 0.84f, 0.0f); // Cor da moldura (dourado)
    } else {
        glColor3f(0.75f, 0.75f, 0.75f); // Cor da moldura (prata)
    }
    glutSolidCube(1.0);
    glPopMatrix();
}

// Função para desenhar a cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e de profundidade
    glLoadIdentity(); // Carrega a matriz de identidade

    gluLookAt(0.0f, 10.0f, 7.0f,    // Posição da câmera
              0.0f, 0.0f, -3.0f,  // Ponto para onde a câmera está olhando
              0.0f, 1.0f, 0.0f);  // Vetor de orientação da câmera

    // Desenhar as paredes da sala
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.5f); // Translada para a posição correta das paredes
    glColor3fv(wallColor); // Define a cor das paredes
    glBegin(GL_QUADS); // Começa a desenhar um quadrilátero
        // Parede traseira
        glVertex3f(-2.5f, 2.5f, 0.0f);
        glVertex3f(2.5f, 2.5f, 0.0f);
        glVertex3f(2.5f, -2.5f, 0.0f);
        glVertex3f(-2.5f, -2.5f, 0.0f);
        // Parede esquerda
        glVertex3f(-2.5f, -2.5f, 4.0f);
        glVertex3f(-2.5f, -2.5f, 0.0f);
        glVertex3f(-2.5f, +2.5f, 0.0f);
        glVertex3f(-2.5f, +2.5f, 4.0f);
        // Parede direita
        glVertex3f(2.5f, 2.5f, 4.0f);
        glVertex3f(2.5f, 2.5f, 0.0f);
        glVertex3f(2.5f, -2.5f, 0.0f);
        glVertex3f(2.5f, -2.5f, 4.0f);
    glEnd(); // Termina de desenhar o quadrilátero
    glPopMatrix();

    // Desenhar quadros nas paredes
    drawFrame(-2.25f, 1.0f, -2.49f); // Quadro na parede traseira
    drawFrame(0.0f, 1.0f, -2.49f);   // Quadro na parede traseira
    drawFrame(2.25f, 1.0f, -2.49f, true);  // Quadro na parede traseira


    // Desenhar o chão preto
    glPushMatrix();
    glColor3fv(floorColor); // Define a cor do chão
    glBegin(GL_QUADS);
        glVertex3f(-2.5f, -2.5f, -2.5f); // Canto inferior esquerdo
        glVertex3f(2.5f, -2.5f, -2.5f);  // Canto inferior direito
        glVertex3f(2.5f, -2.5f, 1.5f);  // Canto superior direito
        glVertex3f(-2.5f, -2.5f, 1.5f); // Canto superior esquerdo
    glEnd();
    glPopMatrix();

    glutSwapBuffers(); // Troca os buffers
}

// Função para redimensionar a janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h); // Define a viewport da janela
    glMatrixMode(GL_PROJECTION); // Define a matriz atual como matriz de projeção
    glLoadIdentity(); // Carrega a matriz de identidade
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0); // Define a perspectiva da câmera
    glMatrixMode(GL_MODELVIEW); // Define a matriz atual como matriz de modelo e visualização
}

// Função para controlar a entrada do teclado
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // Verifica se a tecla pressionada foi ESC
        exit(0); // Sai do programa
    }
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Define o modo de exibição do GLUT
    glutInitWindowSize(WIDTH, HEIGHT); // Define o tamanho da janela
    glutCreateWindow("Museu 3D"); // Cria a janela com o título "Museu 3D"

    init(); // Inicializa a cena
    glutDisplayFunc(display); // Define a função de exibição
    glutReshapeFunc(reshape); // Define a função de redimensionamento da janela
    glutKeyboardFunc(keyboard); // Define a função de controle do teclado

    glutMainLoop(); // Entra no loop principal do GLUT

    return 0; // Retorna 0 (programa encerrado com sucesso)
}
