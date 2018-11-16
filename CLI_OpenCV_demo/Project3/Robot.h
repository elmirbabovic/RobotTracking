#pragma once
#include "MyMath.h"
#include "SlidingPath.h"
#include "Nullable.h"

class Robot
{

	SlidingPath* historijaPozicija = new SlidingPath(30);

	int id;
public:
	bool isRemoved = false;
	NullableType<float> ugaoPravcaKretanja = nullptr;

	float Udaljenost_OdTacke(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovija();
		if (frame_point == nullptr)
			return INT_MAX;

		return Udaljenost_DvijeTacke(frame_point->point, p);
	}

	Robot(int id, int framePozicija, int x, int y)
	{
		this->id = id;
		DodajPoziciju(framePozicija, x, y);
	}

	int GetId()
	{
		return id;
	}

	MotionStep* GetPozicijaNajnovija()
	{
		int velicina = historijaPozicija->getVelicina();
		if (velicina == 0)
			return nullptr;

		MotionStep* frame_point = historijaPozicija->GetNajnovija();
		return frame_point;
	}

	NullableType<int> PravacDeltaY;
	NullableType<int> PravacDeltaX;

	void DodajPoziciju(int framePozicija, int x2, int y2)
	{
		cv::Point p2 = cv::Point(x2, y2);
		int min_steps_for_angle_calc = 10;
		if (historijaPozicija->getVelicina() > min_steps_for_angle_calc)
		{
			MotionStep* mPoint1 = historijaPozicija->getOlderVersion(min_steps_for_angle_calc);

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
		historijaPozicija->dodaj(framePozicija, p2);
	}
};
