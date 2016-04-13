#include <GLUT/GLUT.h>
#include <time.h>

void myDisplay();
void myIdle();
static double theta;
static double beta;

int main(int argc, char *argv[])
{
    theta = 0;
    beta = 50;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400,400);
    glutCreateWindow("HB's Solar System");
    glutDisplayFunc(&myDisplay);
    glutIdleFunc(&myIdle);
    glutMainLoop();
    return 0;
}
void myIdle()
{
    theta = theta + 1;
    beta = beta + 0.5;
    if (theta >= 360.0)theta = 0;
    if (beta >= 360.0)beta = 0;
    //(6);
    myDisplay();
}
void myDisplay()
{
    //glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75,1,20,400);
    //第一个视角，相当于眼皮的张角
    //第二个参数是投影面的横宽比
    //第三个是近裁剪面的距离，第四个是远裁剪面的距离，这样才能正确形成一个空间（太远的不用看了）
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,100,0,0,0,0,1,0);
    {
        GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_light_ambient[]   = {0.1f, 0.1f, 0.1f, 1.0f};
        GLfloat sun_light_diffuse[]   = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT,   sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,   sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }
    glPushMatrix();
    //眼睛的地点、看向的位置、向上的方向（这里是眼睛在z轴，看向xy平面，y向上）
    {
        GLfloat sun_mat_ambient[]   = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_diffuse[]   = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_emission[] = {0.8f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_shininess   = 0.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,    sun_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    sun_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   sun_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   sun_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
        
        //glColor3f(1.0,0,0);
        glutSolidSphere(20,80,80);
    }
    glPopMatrix();
    
    glPushMatrix();
    {
        GLfloat earth_mat_ambient[]   = {0.1f, 0.1f, 0.2f, 1.0f};
        GLfloat earth_mat_diffuse[]   = {0.4f, 0.4f, 0.8f, 1.0f};
        GLfloat earth_mat_specular[] = {0.9f, 0.9f, 1.0f, 1.0f};
        GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.03f, 1.0f};
        GLfloat earth_mat_shininess   = 30.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        
        //glColor3f(0, 0.8, 1.0);
        glRotatef(theta,1,-1,0);
        glTranslatef(30,30,0);
        glutSolidSphere(10, 80, 80);
    }
    glPopMatrix();
    
    glPushMatrix();
    //glLoadIdentity();
    //如果load的话之前的变换白费了？？
    {
        GLfloat earth_mat_ambient[]   = {0.2f, 0.0f, 0.1f, 0.8f};
        GLfloat earth_mat_diffuse[]   = {0.8f, 0.1f, 0.4f, 1.0f};
        GLfloat earth_mat_specular[] = {1.0f, 0.7f, 0.7f, 0.8f};
        GLfloat earth_mat_emission[] = {0.03f, 0.0f, 0.0f, 1.0f};
        GLfloat earth_mat_shininess   = 40.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        
        double theta_delta = (int(theta) + 90) % 360;
        glRotatef(theta_delta, 0, 1, 0);
        glTranslatef(48, 0, 0);
        glutSolidSphere(12, 80, 80);
    }
    glPopMatrix();
    //行星2
    
    glPushMatrix();
    {
        GLfloat earth_mat_ambient[]   = {0.1f, 0.15f, 0.1f, 0.8f};
        GLfloat earth_mat_diffuse[]   = {0.4f, 0.6f, 0.4f, 1.0f};
        GLfloat earth_mat_specular[] = {0.9f, 1.0f, 0.9f, 0.8f};
        GLfloat earth_mat_emission[] = {0.0f, 0.01f, 0.0f, 1.0f};
        GLfloat earth_mat_shininess   = 25.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,    earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,   earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        
        glRotatef(theta, 1, -1, 0);
        glTranslatef(30, 30, 0);
        //绕着太阳转
        glRotatef(beta, 1, 0, 0);
        glTranslatef(0, 15, 0);
        //绕着行星转
        glutSolidSphere(3, 80, 80);
    }
    glPopMatrix();
    //卫星
    
    glFlush();
    glutSwapBuffers();
}