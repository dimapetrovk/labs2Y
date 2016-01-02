#pragma once
class elips {
	float a = 5;//x semiaxis
	float b = 2;//y semiaxis
	const unsigned rastGrid = 30;//size of rasterization grid
public:float x1=-1;
	float y1, X, Y;//rectangle coordinates
public: void draw() {//draw standart elipse func
	glColor3f(0, 1, 0);
	glBegin(GL_LINE_STRIP);
		for (GLfloat x = -a; x <= a; x += 0.01) glVertex2f(x + x1 - a, b * sqrt(1 - pow(x / a, 2)) + y1 + b);//1 vertex of line
		for (GLfloat x = a; x >= -a; x -= 0.01) glVertex2f(x + x1 - a, -b * sqrt(1 - pow(x / a, 2)) + y1 + b);//2 vertex of line
	glEnd();
}
		void swap(float &x1, float &x)//swap func
		{
			x1 += x;
			x = x1 - x;
			x1 -= x;
		}
		void set(float x, float y) {//set elipse inform
			x1 = X;
			y1 = Y;
			if (x1 < x) swap(x1, x);
			if (y < y1)swap(y1, y);
			a = (x1 - x) / 2;
			b = (y - y1) / 2;
		}
		void grid() {//draw grid func
			glColor3f(0, 0, 1);
			glBegin(GL_LINES);
			for (float x = 0; x <= 500; x += 500 / rastGrid) {
				glVertex2f(x, 0);
				glVertex2f(x, 500);		
				glVertex2f(0, x);
				glVertex2f(500, x);
			}
			glEnd();
		}
		void rasterization() {//draw rasterized elipse
			glColor3f(1, 0, 0);//set color
			glBegin(GL_LINE_STRIP);

			unsigned i = (x1 - 2 * a) / (int)(500 / rastGrid);
			float x = (i + 0.5)*(500 / rastGrid);
			if (x <= x1 - 2 * a) i++;
			unsigned t = (int)(y1 + b) / (500 / rastGrid);
			if (y1 + b > (t + 0.5)*(500 / rastGrid))t++;
			glVertex2f(i*(500 / rastGrid), t*(500 / rastGrid));
			unsigned fi, ft, si;//start snd finish grid coordinates
			ft = t;
			si = i;
			while (i <= (x1 - a) / (500 / rastGrid)) {//1 quarter
				node(i, t);//move to next node
				glVertex2f(i*(500 / rastGrid), t*(500 / rastGrid));
			}
			fi=x1 / (int)(500 / rastGrid);
			if (x1 > (fi + 0.5)*(500 / rastGrid)) fi++;
			while (i <= fi && t> ft) {//2 quarter
				node1(i, t);//move to next node
				glVertex2f(i*(500 / rastGrid), t*(500 / rastGrid));
			}
			while (i > (x1 - a) / (500 / rastGrid)) {//3 quarter
				node2(i, t);//move to next node
				glVertex2f(i*(500 / rastGrid), t*(500 / rastGrid));
			}
			while (i >= si && t< ft) {//4 quarter
				node3(i, t);//move to next node
				glVertex2f(i*(500 / rastGrid), t*(500 / rastGrid));
			}
			glEnd();
		}

		void node(unsigned &i, unsigned &t) {
			float x = (i + 0.5)*(500 / rastGrid);
			float y = (t + 0.5)*(500 / rastGrid);
			float d = pow((x - x1 + a) / a, 2) + pow((y - y1 - b) / b, 2);
			if (d > 1) { i++; return; }
			t++;
		}

		void node1(unsigned &i, unsigned &t) {
			float x = (i + 0.5)*(500 / rastGrid);
			float y = (t - 0.5)*(500 / rastGrid);
			float d = pow((x - x1 + a) / a, 2) + pow((y - y1 - b) / b, 2);
			if (d > 1) { t--; return; }
			i++;
		}

		void node2(unsigned &i, unsigned &t) {
			float x = (i - 0.5)*(500 / rastGrid);
			float y = (t - 0.5)*(500 / rastGrid);
			float d = pow((x - x1 + a) / a, 2) + pow((y - y1 - b) / b, 2);
			if (d > 1) { i--; return; }
			t--;
		}

		void node3(unsigned &i, unsigned &t) {
			float x = (i - 0.5)*(500 / rastGrid);
			float y = (t + 0.5)*(500 / rastGrid);
			float d = pow((x - x1 + a) / a, 2) + pow((y - y1 - b) / b, 2);
			if (d > 1) { t++; return; }
			i--;
		}
};