#pragma once
#include "MyMath.h"
#include "MotionHistory.h"
#include "Nullable.h"
#include "ATP/RedPov.h"

enum MoveActionType
{
	wait, move_foreward, move_backward
};

struct MoveAction
{
	MoveActionType actionType;
	float intensity;
	int duration_ms;
};

struct MoveActionMotor
{
	MoveAction leftMotor;
	MoveAction rightMotor;
};


class Robot
{

	MotionHistory* motionHistory = new MotionHistory(30);

	cv::Scalar color;
	int id;
public:	
	RedSekv<MotionStep*>* todoTargetPoints = new RedSekv<MotionStep*>();
	RedSekv<MoveActionMotor*>* todoActions = new RedSekv<MoveActionMotor*>();
	

	bool isRemoved = false;
	NullableType<float> ugaoPravcaKretanja = nullptr;

	float Udaljenost_OdTacke(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovija();
		if (frame_point == nullptr)
			return INT_MAX;

		return Udaljenost_DvijeTacke(frame_point->point, p);
	}

	Robot(int id, int framePozicija, int x, int y, cv::Scalar color)
	{
		this->id = id;
		this->color = color;
		DodajPoziciju(framePozicija, x, y);
	}

	int GetId()
	{
		return id;
	}

	MotionStep* GetPozicijaNajnovija()
	{
		int velicina = motionHistory->Count();
		if (velicina == 0)
			return nullptr;

		MotionStep* frame_point = motionHistory->GetCurrent();
		return frame_point;
	}

	cv::Scalar& GetColor()
	{
		return color;
	}

	int movementsCounter = 0;
	void AddMovementPoint(int x, int y)
	{
		this->todoTargetPoints->dodaj(new MotionStep(movementsCounter, x, y));
		movementsCounter++;
	}

	NullableType<int> PravacDeltaY;
	NullableType<int> PravacDeltaX;

	void DodajPoziciju(int framePozicija, int x2, int y2)
	{
		cv::Point p2 = cv::Point(x2, y2);
		int min_steps_for_angle_calc = 10;
		if (motionHistory->Count() > min_steps_for_angle_calc)
		{
			MotionStep* mPoint1 = motionHistory->GetOlderVersion(min_steps_for_angle_calc);

			if (mPoint1 != nullptr)
			{
				cv::Point p1 = mPoint1->point;
				int Dx = DeltaX(p1, p2);
				int Dy = DeltaY(p1, p2);
				float c = GetC(Dy, Dx);
				if (c > 5)
				{
					this->PravacDeltaX = Dx;
					this->PravacDeltaY = Dy;
					ugaoPravcaKretanja = IzracunajUgao(Dx, Dy);
				}
			}

		}
		motionHistory->Add(framePozicija, p2);
	}
};
