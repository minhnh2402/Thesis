#include "DeltaRobot.h"
#include <cmath>
#include <fstream>


Delta::Delta() {
	// Constructor for the delta class. This function allows you to create an instance of the delta class and sets some properties of the robot.
	PI = 3.14159265358979323846;
	R = 168;
	r = 50;
	d = 45;
	L = 200;
	l = 380;
	a = r - R; // -118
	b = (-sqrt(3) / 2) * (r - R);
	c = 0.5 * (R - r);
	rMax = 200;
	zMin = 253;
	zMax = 605;
}


void Delta::goHome() {
	/* Delta will go to its home position (x,y,z) = (0,0,-47.06) where all joint angles are zero. The robot will report its joint angles to the serial monitor*/
	myTheta.q1 = myTheta.q2 = myTheta.q3 = 0;
	goToAngle(myPoint, myTheta);
	reportAngles();
}

void Delta::goTo(PointStruct& point, ThetaStruct& theta) {
	/* Inputs the target position, (x,y,z). First, this function tests if the target position is in the workspace.
	 If so, it calculates the inverse kineamtics, moves the robot to that position. It not, the robot reports that it isnt in the workspace.
	 Finally, the robot reports its current joint angles.*/
	int inWorkspace = testInWorkspace(point);

	if (inWorkspace) {
		delta_calcInverse(point, theta);
		cout << theta.q1 << endl;
		cout << theta.q2 << endl;
		cout << theta.q3 << endl;
	}
	else {
		cout<< ("NOT IN WORKSPACE");
	}
	reportAngles();
}

int Delta::testInWorkspace(PointStruct& point) {
	/* inputs target x,y, and z position. Tests if the position if the position is in the current worksapce of the robot (set by rMax, zMin, and zMax.
	If the point is in the workspace, return 1, else return 0*/
	float r = sqrt(point.x * point.x + point.y * point.y);
	//  Serial.println(String(" test") + round(x) + String(" ") + round(z) + String(" ") + round(z));
	if ((r <= rMax) && (point.z <= zMax) && (point.z >= zMin)) {
		return 1;
	}
	else {
		return 0;
	}
}

void Delta::reportPosition() {
	/* Report the curent position of the robot*/
	//Serial.print("ATPOS ");
	//Serial.print(x0, 2);
	//Serial.print(" ");
	//Serial.print(y0, 2);
	//Serial.print(" ");
	//Serial.println(z0, 2);
}

void Delta::reportAngles() {
	/* Report the current position of the robot*/
	/*Serial.println(String("ATANG ") + round(t1) + String(" ") + round(t2) + String(" ") + round(t3));*/
}

void Delta::goToAngle(PointStruct& point, ThetaStruct& theta) {
	/* inputs angles angle1-3. Claculates forward kineamtics and tests if position is in the workspace. If so, the robot goes to those angles.
	 *  If not, the root reports that it is not in the workspace. Then, report the position of the robot. */


	delta_calcForward(point, theta);
	int inWorkspace = testInWorkspace(point);
	if (inWorkspace) {
		//t1 = angle1;
		//t2 = angle2;
		//t3 = angle3;
		//servo1.write(-t1 + 90);
		//servo2.write(-t2 + 90);
		//servo3.write(-t3 + 90);
		cout << theta.q1;
		cout << theta.q2;
		cout << theta.q3;
	}
	else {
		cout << ("NOT IN WORKSPACE");
	}
	reportPosition();

}



void Delta::delta_calcInverse(PointStruct& point, ThetaStruct& theta) {

	double E1 = -2 * L * (point.y + a);
	double F1 = -2 * L * (point.z - d);
	double G1 = pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2) + pow(L, 2)
		+ pow(a, 2) + pow(d, 2) + 2 * point.y * a - 2 * point.z * d - pow(l, 2);

	double E2 = L * (sqrt(3) * (point.x + b) + point.y + c);
	double F2 = -2 * L * (point.z - d);
	double G2 = pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2) + pow(L, 2)
		+ pow(b, 2) + pow(c, 2) + pow(d, 2) + 2 * point.x * b + 2 * point.y * c - 2 * point.z * d - pow(l, 2);

	double E3 = L * (-sqrt(3) * (point.x - b) + point.y + c);
	double F3 = -2 * L * (point.z - d);
	double G3 = pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2) + pow(L, 2)
		+ pow(b, 2) + pow(c, 2) + pow(d, 2) - 2 * point.x * b + 2 * point.y * c - 2 * point.z * d - pow(l, 2);

	double t11 = (-F1 + sqrt(pow(E1, 2) + pow(F1, 2) - pow(G1, 2))) / (G1 - E1);
	double t12 = (-F1 - sqrt(pow(E1, 2) + pow(F1, 2) - pow(G1, 2))) / (G1 - E1);

	double t21 = (-F2 + sqrt(pow(E2, 2) + pow(F2, 2) - pow(G2, 2))) / (G2 - E2);
	double t22 = (-F2 - sqrt(pow(E2, 2) + pow(F2, 2) - pow(G2, 2))) / (G2 - E2);

	double t31 = (-F3 + sqrt(pow(E3, 2) + pow(F3, 2) - pow(G3, 2))) / (G3 - E3);
	double t32 = (-F3 - sqrt(pow(E3, 2) + pow(F3, 2) - pow(G3, 2))) / (G3 - E3);

	theta.q1 = 2 * (double)atanf(t12) * (180 / PI);
	theta.q2 = 2 * (double)atanf(t22) * (180 / PI);
	theta.q3 = 2 * (double)atanf(t32) * (180 / PI);

}

void Delta::delta_calcForward(PointStruct& point, ThetaStruct& theta) {

	theta.q1 = theta.q1;
	theta.q2 = theta.q2;
	theta.q3 = theta.q3;

	double y1 = (-a + L * cos(theta.q1 * PI / 180));
	double z1 = L * sin(theta.q1 * PI / 180) + d;

	double y2 = -(-a + L * cos(theta.q2 * PI / 180)) * sin(30 * PI / 180);
	double x2 = y2 * tan(60 * PI / 180);
	double z2 = L * sin(theta.q2 * PI / 180) + d;

	double y3 = -(-a + L * cos(theta.q3 * PI / 180)) * sin(30 * PI / 180);
	double x3 = -y3 * tan(60 * PI / 180);
	double z3 = L * sin(theta.q3 * PI / 180) + d;

	double dnm = (y2 - y1) * x3 - (y3 - y1) * x2;
	double w1 = pow(y1, 2) + pow(z1, 2);
	double w2 = pow(x2, 2) + pow(y2, 2) + pow(z2, 2);
	double w3 = pow(x3, 2) + pow(y3, 2) + pow(z3, 2);

	double a1 = (z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1);
	double b1 = -((w2 - w1) * (y3 - y1) - (w3 - w1) * (y2 - y1)) / 2.0;

	double a2 = -(z2 - z1) * x3 + (z3 - z1) * x2;
	double b2 = ((w2 - w1) * x3 - (w3 - w1) * x2) / 2.0;

	double a = a1 * a1 + a2 * a2 + dnm * dnm;
	double b = 2 * (a1 * b1 + a2 * (b2 - y1 * dnm) - z1 * dnm * dnm);
	double c = (b2 - y1 * dnm) * (b2 - y1 * dnm) + b1 * b1 + dnm * dnm * (z1 * z1 - l * l);

	double d1 = pow(b, 2) - 4.0 * a * c;


	point.z = -0.5 * (b - sqrt(d1)) / a;
	point.x = (a1 * point.z + b1) / dnm;
	point.y = (a2 * point.z + b2) / dnm;
	cout << point.x << endl;
	cout << point.y << endl;
	cout << point.z << endl;

}

void Delta::delta_calcOmega(PointStruct& point, ThetaStruct& theta, PointStruct& veclocity) {
	double J1_x, J1_y, J1_z, J2_x, J2_y, J2_z, J3_x, J3_y, J3_z;
	double J1_q1, J1_q2, J1_q3, J2_q1, J2_q2, J2_q3, J3_q1, J3_q2, J3_q3;
	Matrix3d Jx;
	Matrix3d Jq;
	Vector3d omega;
	Vector3d vel;
	
	vel << veclocity.x, veclocity.y, veclocity.z;

	J1_x = point.x;
	J1_y = a + point.y - L * cos(theta.q1 * PI / 180);
	J1_z = - (d - point.z + L * sin(theta.q1 * PI / 180));	 
	J2_x = 2 * (b + point.x) + sqrt(3) * L * cos(theta.q2 * PI / 180);
	J2_y = 2 * (c + point.y) + L * cos(theta.q2 * PI / 180);
	J2_z = -2 * (d - point.z + L * sin(theta.q2 * PI / 180));
	J3_x = 2 * (-b + point.x) - sqrt(3) * L * cos(theta.q3 * PI / 180);
	J3_y = 2 * (c + point.y) + L * cos(theta.q3 * PI / 180);;
	J3_z = -2 * (d - point.z + L * sin(theta.q3 * PI / 180));;
	
	J1_q1 = -2 * L * (cos(theta.q1 * PI / 180) * (d - point.z) + sin(theta.q1 * PI / 180) * (a + point.y));
	J1_q2 = 0;
	J1_q3 = 0;
	J2_q1 = 0;
	J2_q2 = -(L * cos(theta.q2 * PI / 180) * (2 * d - 2 * point.z) - L * sin(theta.q2 * PI / 180) * (c + point.y + sqrt(3) * (b + point.x)));
	J2_q3 = 0;
	J3_q1 = 0;
	J3_q2 = 0;
	J3_q3 = (-L * cos(theta.q3 * PI / 180) * (2 * d - 2 * point.z) + L * sin(theta.q3 * PI / 180) * (c + point.y + sqrt(3) * (b - point.x)));;

	Jx << J1_x, J1_y, J1_z, J2_x, J2_y, J2_z, J3_x, J3_y, J3_z;
	Jq << J1_q1, J1_q2, J1_q3, J2_q1, J2_q2, J2_q3, J3_q1, J3_q2, J3_q3;

	omega = Jq.inverse() * Jx * vel;
	std::cout << omega << endl;
}

void Delta::convertPulse(ThetaStruct& theta_rad, ThetaStruct_INT32& theta_pulse)
{
	theta_pulse.q1 = theta_rad.q1 * 12500 / 9;
	theta_pulse.q2 = theta_rad.q2 * 12500 / 9;
	theta_pulse.q3 = theta_rad.q3 * 12500 / 9;

}

void Delta::convertRad(ThetaStruct& theta_pulse, ThetaStruct& theta_rad)
{
	theta_rad.q1 = theta_pulse.q1 * (PI / 180);
	theta_rad.q2 = theta_pulse.q2 * (PI / 180);
	theta_rad.q3 = theta_pulse.q3 * (PI / 180);

}

void Delta::circleMove(double h, double R, int time, double step)
{
	double t = 0;
	//PointStruct c_PMove;
	//PointStruct c_VMove;
	//ThetaStruct c_TMove;
	//ThetaStruct_INT32 c_PulseMove;
	for (int i = 0; i < ((int)(time/step) + 1); i++)
	{
		t = step * i;
		c_PMove.x = R * sin(2 * PI * t / time);
		c_PMove.y = R * cos(2 * PI * t / time);
		c_PMove.z = h;
		
		c_VMove.x = (2 * PI  / time) * R * cos(2 * PI * t / time);
		c_VMove.y = -(2 * PI / time) * R * sin(2 * PI * t / time);
		c_VMove.z = 0;

		int inWorkspace = testInWorkspace(c_PMove);
		if (inWorkspace) {
			/*cout << ("IN WORKSPACE");*/
			delta_calcInverse(c_PMove, c_TMove);
			
			convertPulse(c_TMove, c_PulseMove);
			jointValue.push_back(c_TMove);
			c_PulseVector.push_back(c_PulseMove);

		}
		else {
			cout << ("NOT IN WORKSPACE");
		}
	}


		std::ofstream outputFile("output.txt"); // Mở tệp để ghi

		if (outputFile.is_open()) {
			for (int i = 0; i < jointValue.size(); ++i) {
				outputFile << jointValue[i].q1 << "\n";
			}
			outputFile << "/////////////////";
			for (int i = 0; i < jointValue.size(); ++i) {
				outputFile << jointValue[i].q2 << "\n";
			}
			outputFile << "/////////////////";
			for (int i = 0; i < jointValue.size(); ++i) {
				outputFile << jointValue[i].q3 << "\n";// Ghi giá trị từng phần tử vào tệp
			}
			outputFile << "/////////////////";

		outputFile.close(); // Đóng tệp
		std::cout << "Xuất dữ liệu thành công." << std::endl;
}
		else {
			std::cerr << "Không thể mở tệp." << std::endl;
		}
}