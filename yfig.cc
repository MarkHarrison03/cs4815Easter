
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string.h>
#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
# endif
#define THICK 1
#define THIN 2
#define RED 3
#define GREEN 4
#define BLUE 5
#define QUIT 6
GLsizei winWidth = 1920, winHeight = 1080; 
GLsizei clipWidth, clipHeight;
bool middleButton = false;
int downX, downY;
GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;
float size = 17.0f;
float r = 0.0f;
float g = 0.0f;
float b = 1.0f;
bool lineMode = false;
bool circleMode = false;
bool rectangleMode = false;

class properties{
	public:
		GLfloat xwcMin, xwcMax, ywcMin, ywcMax;
};

class wcPt2D {
   public:
      GLfloat x, y;
};

int i = 0;
int rectangleI = 0;
int circleI = 0;
wcPt2D points[500];
wcPt2D pointsRectangle[500];
wcPt2D pointsCircle[500];
properties pointsData[500];
properties pointsDataRectangle[500];
properties pointsDataCircle[500];




 
int lineOnex, lineOney, lineTwox, lineTwoy;
	
	void reshapeFunction(GLint newWidth, GLint newHeight){
	clipWidth = newWidth;
	clipHeight = newHeight;
		//glMatrixMode(GL_PROJECTION);
  	  glLoadIdentity( );
		winHeight = newHeight;
		winWidth = newWidth;
	  glViewport (0, 0, 1920 ,  1080);

   	  
	
      gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

      glutPostRedisplay();
	
	}
	
	void init(){
	glClearColor(1.0,1.0,1.0,0.0);
	for(int ind = 0; ind < 50; ind++){
	points[ind].x = 0.0;
	points[ind].y = 0.0;
	

}
	}
	

	wcPt2D normalize(wcPt2D a, int j){
		wcPt2D newPoints;
		float newA =  a.x * (pointsData[j].xwcMax - pointsData[j].xwcMin) / winWidth + pointsData[j].xwcMin;
		float newB = (winHeight - a.y) * (pointsData[j].ywcMax - pointsData[j].ywcMin) / winHeight + pointsData[j].ywcMin ;
		newPoints.x = newA;
		newPoints.y = newB - 4.5;
		return newPoints;
	
	}
	
	wcPt2D normalizeRect(wcPt2D a, int j){
		wcPt2D newPoints;
		float newA =  a.x * (pointsDataRectangle[j].xwcMax - pointsDataRectangle[j].xwcMin) / winWidth + pointsDataRectangle[j].xwcMin;
		float newB = (winHeight - a.y) * (pointsDataRectangle[j].ywcMax - pointsDataRectangle[j].ywcMin) / winHeight + pointsDataRectangle[j].ywcMin ;
		newPoints.x = newA;
		newPoints.y = newB -4.5;
		return newPoints;
	
	}
	
	wcPt2D normalizeCircle(wcPt2D a, int j){
		wcPt2D newPoints;
		float newA =  a.x * (pointsDataCircle[j].xwcMax - pointsDataCircle[j].xwcMin) / winWidth + pointsDataCircle[j].xwcMin;
		float newB = (winHeight - a.y) * (pointsDataCircle[j].ywcMax - pointsDataCircle[j].ywcMin) / winHeight + pointsDataCircle[j].ywcMin ;
		newPoints.x = newA;
		newPoints.y = newB -4.5;
		return newPoints;
	
	}
	
	void displayFunc(){
		
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0,0.0,1.0);
		
		//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mousePosx);
		glLineWidth(1.0f);
		glBegin(GL_LINES);
		
		glVertex2i( 300 ,0);
		glVertex2i(-300,0);
		
		glVertex2i(0,300);
		glVertex2i(0,-300);
		
		
		glEnd();
		
		glFlush();
		glColor3f(r,g,b);
		glLineWidth(size);
		glBegin(GL_LINES);

		int j = 0;
		while( j < i){
			if(points[j+1].x != 0 && points[j+1].y != 0){
		
				wcPt2D newPointOne = normalize(points[j],j);
				wcPt2D newPointTwo = normalize(points[j+1],j);
			glVertex2f(newPointOne.x , newPointOne.y  );
			glVertex2f(newPointTwo.x, newPointTwo.y );
			}
			j+= 2;
		
		}
		glFlush();
		glEnd();
		
		
		glBegin(GL_LINES);

		int k = 0;
		while( k < rectangleI){
		std::cout << rectangleI << std::endl;
		
			if(pointsRectangle[k+1].x != 0 && pointsRectangle[k+1].y != 0){
		
				wcPt2D newPointOne = normalizeRect(pointsRectangle[k],k);
				wcPt2D newPointTwo = normalizeRect(pointsRectangle[k+1],k);
			/*	
			float distanceX;
			if (newPointOne.x <= newPointTwo.x){
				distanceX = newPointTwo.x - newPointOne.x;
			}else{
				distanceX = newPointOne.x - newPointTwo.x;
			}
			float distanceY;
			if (newPointOne.y <= newPointTwo.y){
				distanceY = newPointTwo.y - newPointOne.y;
			}else{
				distanceY = newPointOne.y - newPointTwo.y;
			}
			*/
		
			glVertex2f(newPointOne.x , newPointOne.y  );
			glVertex2f(newPointTwo.x, newPointOne.y );
			
			glVertex2f(newPointTwo.x, newPointOne.y);
			glVertex2f(newPointTwo.x, newPointTwo.y);
			
			glVertex2f(newPointTwo.x, newPointTwo.y);
			glVertex2f(newPointOne.x, newPointTwo.y);
			
			glVertex2f(newPointOne.x, newPointTwo.y);
			glVertex2f(newPointOne.x, newPointOne.y);
			}
			k+= 2;
		
		}
		glutPostRedisplay();
		glFlush();
		glEnd();
		glPointSize(size);
		glBegin(GL_POINTS);
		int l = 0;
		
		std::cout << "HELLO" << std::endl;
		while(l < circleI){
		std::cout <<"HWA" << std::endl;
					if(pointsCircle[l+1].x != 0 && pointsCircle[l+1].y != 0){
					GLfloat x, y, angle;
					wcPt2D newPoints= normalizeCircle(pointsCircle[l+1], l);
					
					for(angle = 0.0f; angle <= (2.0f * 3.1415962); angle += 0.01f){
						x = newPoints.x * sin(angle);
						y = newPoints.y * cos(angle);
						glVertex2f(x,y);

					}
						
			
				}
					l+= 2;
				}

				glutPostRedisplay();
				glFlush();
				glEnd();
						
		glutSwapBuffers();
	}
	
	void motionFunction(int x, int y){
	if(middleButton){
		xwcMin -= (x- downX) / 8;
		xwcMax -= ( x - downX) / 8;
		ywcMin -= (downY - y) / 8;
		ywcMax -= (downY - y) / 8	;
	}
	downX = x;
	downY = y;
	reshapeFunction(winWidth, winHeight);
		
	}
	

	void mouseFunc(int button, int state, int mx, int my){

	//mousePosx = std::to_string(mx);
	//mousePosy = std::to_string(my);
			if(i > 500){
			i = 0;
			}
			if(circleI > 500){
			circleI = 0;
			}
			if(rectangleI > 500){
			rectangleI = 0;
			}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){

			if(lineMode){

			points[i].x = mx;
			points[i].y = my;
			properties newProperty;
			newProperty.xwcMin = xwcMin;
			newProperty.xwcMax = xwcMax;
			newProperty.ywcMin = ywcMin;
			newProperty.ywcMax = ywcMax;
			pointsData[i] = newProperty;
			
			i++;

			displayFunc();
			}
			
			
			if(rectangleMode){
					pointsRectangle[rectangleI].x = mx;
					pointsRectangle[rectangleI].y = my;
					properties newProperty;
					newProperty.xwcMin = xwcMin;
					newProperty.xwcMax = xwcMax;
					newProperty.ywcMin = ywcMin;
					newProperty.ywcMax = ywcMax;
					pointsDataRectangle[rectangleI] = newProperty; 
					rectangleI++;
					displayFunc();

			}
			
			if(circleMode){
			std::cout << " gaioghw" << std::endl;
					pointsCircle[circleI].x = mx;
					pointsCircle[circleI].y = my;
					properties newProperty;
					newProperty.xwcMin = xwcMin;
					newProperty.xwcMax = xwcMax;
					newProperty.ywcMin = ywcMin;
					newProperty.ywcMax = ywcMax;
					pointsDataCircle[rectangleI] = newProperty;
					circleI++; 
					displayFunc();
			}
		}	
		
		//
		if(button == GLUT_MIDDLE_BUTTON){
	
		downX = mx;
		downY = my;
		middleButton = true;
		
		}else{
			middleButton = false;
		}
		
		if((GLUT_ACTIVE_CTRL & glutGetModifiers()) > 0){
		downX = mx; 
		downY = my;
		if(button == GLUT_WHEEL_UP){

		xwcMin /= 1.1;
		xwcMax /= 1.1;
		ywcMin /= 1.1;
		ywcMax /= 1.1;
	
		}else if (button == GLUT_WHEEL_DOWN){

		xwcMin *= 1.1;
		xwcMax *= 1.1;
		ywcMin *=1.1;
		ywcMax *=1.1;
	 
		}
	reshapeFunction(winWidth, winHeight);
	}
	}
	
	
void keyboardFunc(unsigned char key, int x, int y){

  if(key=='l' || key=='L'){
    lineMode  = true ;
    rectangleMode = false;
    circleMode = false;

    glutPostRedisplay();
    }else if(key == 'r' || key == 'R'){
    lineMode = false;
    rectangleMode = true;
    circleMode = false;

        glutPostRedisplay();
    }else if(key == 'c' || key == 'C'){
    lineMode = false;
    rectangleMode = false;
    circleMode = true;
    }
}
void processMenuEvents(int option){
  
  switch(option){
  	case RED: r = 1.0f; g = 0.0f; b = 0.0f ;break;
  	case GREEN:r = 0.0f; g = 1.0f; b = 0.0f ;break;
  	case BLUE: r = 0.0f; g = 0.0f; b = 1.0f ;break;
  	case THICK: size = 15.0f; break;
  	case THIN : size = 1.0f; break; 
  
  }
}
	
	void createGLUTMenus(){
  int menu, thicknessSubmenu, colorSubmenu;
  thicknessSubmenu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Thick", THICK);
  glutAddMenuEntry("Thin", THIN);
  

  colorSubmenu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Red", RED);
  glutAddMenuEntry("Green", GREEN);
  glutAddMenuEntry("Blue", BLUE);
  
  

  menu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("Quit", QUIT);
  glutAddSubMenu("Thickness", thicknessSubmenu);
  glutAddSubMenu("Color", colorSubmenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv){
	
	glutInit(&argc, argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(winWidth,winHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE );
	glutCreateWindow("Easter");
	
	init();
	
	glutMouseFunc(mouseFunc);
	glutDisplayFunc(displayFunc);
	    createGLUTMenus();
	glutKeyboardFunc(keyboardFunc);
	glutMotionFunc(motionFunction);
	glutReshapeFunc(reshapeFunction);
	
	glutMainLoop();
	return 0;
}
