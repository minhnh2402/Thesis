#include "Header.h"
#include "DeltaRobot.h"



int main()
{	
	Delta* MyRobot;
	MyRobot = new Delta();
	PointStruct myPoint;
	ThetaStruct  myTheta_p;
	myTheta_p.q1 = 30;
	myTheta_p.q2 = 30;
	myTheta_p.q3 = 30;

	MyRobot->delta_calcForward(myPoint, myTheta_p);
	//for (auto it : MyRobot->c_PulseVector)
	//{
	//	cout << *it.q1 << endl;
	//}
	//cout << MyRobot->c_PulseVector.size() << endl;
	//cout << MyRobot->c_PulseMove.q1 << endl;
	//for (int i = 0; i < MyRobot->c_PulseVector.size(); i++)
	//{
	//	cout << MyRobot->c_PulseVector[i].q1 << endl;
	//}

	
	
}

