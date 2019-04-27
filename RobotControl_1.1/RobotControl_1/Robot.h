#pragma once
#include "MyMath.h"
#include "MotionHistory.h"
#include "AngleHistory.h"
#include "Nullable.h"
#include "ATP/RedPov.h"

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

	MotionHistory* motionHistoryFront = new MotionHistory(30);
	MotionHistory* motionHistoryRear = new MotionHistory(30);
	
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

	Lista<cv::Point>* PredictPath()
	{
		ListaPov<cv::Point> *result = new ListaPov<cv::Point>;

		int velicina = motionHistoryFront->Count();
		if (velicina == 0)
			return result;

		


		for(int i=velicina-1; i>=0;i--)
		{
			cv::Point p = motionHistoryFront->GetOlderVersion(i)->point;
			
			result->Add(cv::Point(p.x , p.y ));
		}

		//ovdje ide for za predikciju po double exponential smoothing za jos 10 tacaka
				

		return result;
		
	}


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
