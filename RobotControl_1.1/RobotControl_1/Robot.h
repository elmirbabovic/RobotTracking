#pragma once
#include "MyMath.h"
#include "MotionHistory.h"
#include "AngleHistory.h"
#include "Nullable.h"
#include "ATP/RedPov.h"
#include "IPredictAlgorithm.h"
#include "double_smothing_ex.h"

enum PointType
{
	frontPoint, rearPoint
};

//enum MoveActionType
//{
//	wait, move_foreward, move_backward
//};
//
//struct MoveAction
//{
//	MoveActionType actionType;
//	float intensity;
//	int duration_ms;
//};
//
//struct MoveActionMotor
//{
//	MoveAction leftMotor;
//	MoveAction rightMotor;
//};


class Robot
{
	int brojac=0;//only for logic debugging
	MotionHistory* motionHistoryFront = new MotionHistory(55);
	MotionHistory* motionHistoryRear = new MotionHistory(55);
	
	cv::Scalar color;
	int id;
	NullableType<int> PravacDeltaY = nullptr;
	NullableType<int> PravacDeltaX = nullptr;
	bool isRemoved = false;
	int movementsCounter = 0;
	NullableType<float> ugaoPravcaKretanja = nullptr;
public:	
	RedSekv<MotionStep*>* todoTargetPoints = new RedSekv<MotionStep*>();
	//RedSekv<MoveActionMotor*>* todoActions = new RedSekv<MoveActionMotor*>();
	//AngleHistory* angleHistory = new AngleHistory(30);
	float Udaljenost_OdTackeFront(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovijaFront();
		if (frame_point == nullptr)
			return INT_MAX;

		return MyMath::Udaljenost_DvijeTacke(frame_point->point, p);
	}

	float Udaljenost_OdTackeRear(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovijaRear();
		if (frame_point == nullptr)
			return INT_MAX;

		return MyMath::Udaljenost_DvijeTacke(frame_point->point, p);
	}
	double_smothing_ex* predict_algorithm = new double_smothing_ex;
	Lista<cv::Point>* PredictPath()
	{
		return predict_algorithm->PredictPath(motionHistoryFront, 50);
	}
	//Lista<cv::Point>* PredictPath()
	//{
	//	//smoothing factors alpha and beta
	//	float alpha = 0.3;
	//	float beta = 0.5;

	//	ListaPov<cv::Point> *result = new ListaPov<cv::Point>;

	//	int velicina = motionHistoryFront->Count();
	//	if (velicina < 30)
	//		return result;

	//	for(int i=velicina-1; i>=0;i--)
	//	{
	//		cv::Point p = motionHistoryFront->GetOlderVersion(i)->point;
	//		
	//		result->Add(cv::Point(p.x , p.y ));
	//	}

	//

	//	//ovdje ide for za predikciju po double exponential smoothing za jos 10 tacaka
	//	const int predictionSize = 40;
	//	float sX[predictionSize];
	//	float bX[predictionSize];
	//	float yX[predictionSize+1];
	//	float sY[predictionSize];
	//	float bY[predictionSize];
	//	float yY[predictionSize+1];
	//	float datX[predictionSize];
	//	float datY[predictionSize];

	//	cv::Point predictionResult[predictionSize];

	//	datX[0] = alpha * result->get(0).x + result->get(0).x;
	//	datY[0] = alpha * result->get(0).y + result->get(0).y;

	//	for (int i = 1; i < 30; i++)
	//	{
	//		datX[i] = alpha * result->get(i).x + (1-alpha)*result->get(i-1).x;
	//		datY[i] = alpha * result->get(i).y + (1 - alpha)*result->get(i - 1).y;
	//	}


	//	sX[0] = result->get(0).x;
	//	sY[0] = result->get(0).y;
	//	yX[0] = datX[0];
	//	yY[0] = datY[0];
	//	sX[1] = datX[1];
	//	sY[1] = datY[1];
	//	bX[0] = 1;//data[1]-data[0];
	//	bY[0] = 1;//data[1]-data[0];
	//	bX[1] = result->get(1).x - result->get(0).x;
	//	bY[1] = result->get(1).y - result->get(0).y;

	//	int i = 1;
	//	yX[0] = sX[0] + bX[0];
	//	yY[0] = sY[0] + bY[0];
	//	yX[1] = sX[1] + 2 * bX[1];
	//	yY[1] = sY[1] + 2 * bY[1];

	//	for (i = 2; i < 30; i++) {
	//		sX[i] = alpha * datX[i] + (1 - alpha) * (sX[i - 1] + bX[i - 1]);
	//		sY[i] = alpha * datY[i] + (1 - alpha) * (sY[i - 1] + bY[i - 1]);
	//		bX[i] = (beta * (sX[i] - sX[i - 1])) + (1 - beta) * bX[i - 1];
	//		bY[i] = (beta * (sY[i] - sY[i - 1])) + (1 - beta) * bY[i - 1];
	//		yX[i + 1] = sX[i] + i * bX[i];
	//		yY[i + 1] = sY[i] + i * bY[i];
	//	}

	//	for (i=29; i < 40; i++) {
	//		sX[i] = alpha * sX[i-1] + (1 - alpha) * (sX[i - 1] + bX[i - 1]);
	//		sY[i] = alpha * sY[i-1] + (1 - alpha) * (sY[i - 1] + bY[i - 1]);
	//		bX[i] = (beta * (sX[i] - sX[i - 1])) + (1 - beta) * bX[i - 1];
	//		bY[i] = (beta * (sY[i] - sY[i - 1])) + (1 - beta) * bY[i - 1];
	//		yX[i + 1] = sX[i] + i * bX[i];
	//		yY[i + 1] = sY[i] + i * bY[i];
	//	}

	//	for (int j = 0; j < 10; j++) {
	//		yX[j + 30] = sX[j + 29] + (j + 30)*bX[j + 29];
	//		yY[j + 30] = sY[j + 29] + (j + 30)*bY[j + 29];
	//	}

	//	for(int a=0;a<40;a++)
	//	{
	//		predictionResult[a].x = yX[a];
	//		predictionResult[a].y = yY[a];
	//	}

	//	for (int t = 0; t < predictionSize; t++)
	//	{
	//		result->Add(predictionResult[t]);
	//	}
	//	brojac++;
	//	if (brojac%50==0)
	//	{
	//		ofstream f("result.txt", ios::app);
	//		f << "--------------------------" << endl;
	//		f << "Novi ispis: " << brojac <<endl;
	//		for (int j = 0; j < 40; ++j)
	//		{
	//			f << result->get(j).x << "," << result->get(j).y << endl;
	//		}
	//		f.close();
	//	}
	//	return result;
	//	
	//}


	Robot(int id, int frameId, int x, int y, cv::Scalar color, PointType pointType)
	{
		this->id = id;
		this->color = color;
		SaveNewPosition(frameId, x, y, pointType);
	}

	int GetId()
	{
		return id;
	}

	MotionStep* GetPozicijaNajnovijaFront()
	{
		int velicina = motionHistoryFront->Count();
		if (velicina == 0)
			return nullptr;

		MotionStep* frame_point = motionHistoryFront->GetCurrent();
		return frame_point;
	}

	MotionStep* GetPozicijaNajnovijaRear()
	{
		int velicina = motionHistoryRear->Count();
		if (velicina == 0)
			return nullptr;

		MotionStep* frame_point = motionHistoryRear->GetCurrent();
		return frame_point;
	}

	cv::Scalar& GetColor()
	{
		return color;
	}


	void AddMovementPoint(int x, int y)
	{
		this->todoTargetPoints->dodaj(new MotionStep(movementsCounter, x, y));
		movementsCounter++;
	}


	void SaveNewPosition(int frameId, int x, int y, PointType pointType)
	{
		cv::Point p2 = cv::Point(x, y);

		if (!this->todoTargetPoints->isPrazan())
		{
			MotionStep* targetPoint = this->todoTargetPoints->getSaPozicije(0);
			cv::Point p1 = targetPoint->point;
			float udaljenost = MyMath::Udaljenost_DvijeTacke(p1, p2);
			if (udaljenost < 40)
			{
				this->todoTargetPoints->ukloni();
			}
		}
			

		
		int min_steps_for_angle_calc = 3;
		/*if (motionHistory->Count() > min_steps_for_angle_calc)
		{
			MotionStep* mPoint1 = motionHistory->GetOlderVersion(min_steps_for_angle_calc);

			if (mPoint1 != nullptr)
			{
				cv::Point p1 = mPoint1->point;
				int Dx = MyMath::DeltaX(p1, p2);
				int Dy = MyMath::DeltaY(p1, p2);
				float c = MyMath::GetC(Dy, Dx);
				if (c > 2)
				{
					this->PravacDeltaX = Dx;
					this->PravacDeltaY = Dy;
					ugaoPravcaKretanja = MyMath::IzracunajUgao(Dx, Dy);
					angleHistory->Add(frameId, ugaoPravcaKretanja);
				}
			}

		}*/
		if (pointType==frontPoint)
			motionHistoryFront->Add(frameId, p2);

		if (pointType == rearPoint)
			motionHistoryRear->Add(frameId, p2);
	}

	void Remove()
	{
		this->isRemoved = true;
	}

	bool GetIsRemoved()
	{
		return isRemoved;
	}
	//float izracunajProsjek(int broj)
	//{
	//	//proba exponencijalnog smoothing-a
	//	float alfa = 0.7;
	//	float ugao = angleHistory->GetOlderVersion(broj+1)->point;
	//	for (int i = broj; i >=0; i--)
	//	{
	//		float ugao = ugao * (1-alfa) + angleHistory->GetOlderVersion(i+1)->point*alfa;
	//	}
	//	//Elmirov smoothing :-)
	//	if (((ugao + 360) - (angleHistory->GetOlderVersion(10)->point + 360)) > 3)
	//		return angleHistory->GetOlderVersion(10)->point + 3;
	//	else if (((ugao + 360) - (angleHistory->GetOlderVersion(10)->point + 360)) < -3)
	//		return angleHistory->GetOlderVersion(10)->point - 3;
	//	else
	//		return ugao;
	//}

	NullableType<float> GetUgaoPravcaKretanja()
	{
		//proba smoothinga nenormalnog
		
		//if (angleHistory->Count() > 10)
		//	return izracunajProsjek(9);
		////kraj nenormalnog smoothong-a
		//else

		MotionStep* positionFront = GetPozicijaNajnovijaFront();
		MotionStep* positionRear = GetPozicijaNajnovijaRear();
		if (positionFront == nullptr || positionRear == nullptr)
			return nullptr;


		int  dx = MyMath::DeltaX(positionFront->point, positionRear->point);
		int  dy = MyMath::DeltaY(positionFront->point, positionRear->point);

		ugaoPravcaKretanja = MyMath::IzracunajUgao(dx, dy);

			return ugaoPravcaKretanja;
	}

	NullableType<int> GetPravacDeltaY()
	{
		return PravacDeltaY;
	}

	NullableType<int> GetPravacDeltaX()
	{
		return PravacDeltaX;
	}
};
