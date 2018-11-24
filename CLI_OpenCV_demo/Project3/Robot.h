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
	NullableType<int> PravacDeltaY = nullptr;
	NullableType<int> PravacDeltaX = nullptr;
	bool isRemoved = false;
	int movementsCounter = 0;
	NullableType<float> ugaoPravcaKretanja = nullptr;
public:	
	RedSekv<MotionStep*>* todoTargetPoints = new RedSekv<MotionStep*>();
	RedSekv<MoveActionMotor*>* todoActions = new RedSekv<MoveActionMotor*>();
	
	float Udaljenost_OdTacke(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovija();
		if (frame_point == nullptr)
			return INT_MAX;

		return MyMath::Udaljenost_DvijeTacke(frame_point->point, p);
	}

	Robot(int id, int frameId, int x, int y, cv::Scalar color)
	{
		this->id = id;
		this->color = color;
		SaveNewPosition(frameId, x, y);
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


	void AddMovementPoint(int x, int y)
	{
		this->todoTargetPoints->dodaj(new MotionStep(movementsCounter, x, y));
		movementsCounter++;
	}


	void SaveNewPosition(int frameId, int x, int y)
	{
		cv::Point p2 = cv::Point(x, y);
		int min_steps_for_angle_calc = 10;
		if (motionHistory->Count() > min_steps_for_angle_calc)
		{
			MotionStep* mPoint1 = motionHistory->GetOlderVersion(min_steps_for_angle_calc);

			if (mPoint1 != nullptr)
			{
				cv::Point p1 = mPoint1->point;
				int Dx = MyMath::DeltaX(p1, p2);
				int Dy = MyMath::DeltaY(p1, p2);
				float c = MyMath::GetC(Dy, Dx);
				if (c > 5)
				{
					this->PravacDeltaX = Dx;
					this->PravacDeltaY = Dy;
					ugaoPravcaKretanja = MyMath::IzracunajUgao(Dx, Dy);
				}
			}

		}
		motionHistory->Add(frameId, p2);
	}

	void Remove()
	{
		this->isRemoved = true;
	}

	bool GetIsRemoved()
	{
		return isRemoved;
	}

	NullableType<float> GetUgaoPravcaKretanja()
	{
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
