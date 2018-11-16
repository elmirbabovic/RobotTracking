#pragma once
#include "MyMath.h"
#include "SlidingPath.h"

class Robot
{

	SlidingPath* historijaPozicija = new SlidingPath(30);

	int id;
public:
	int* lastDx = 0;
	int* lastDy = 0;
	bool isRemoved = false;
	float* ugaoPravcaKretanja = nullptr;

	float Udaljenost_OdTacke(cv::Point p)
	{
		MotionStep* frame_point = this->GetPozicijaNajnovija();
		if (frame_point == nullptr)
			return INT_MAX;

		return Udaljenost_DvijeTacke(frame_point->item, p);
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

	void DodajPoziciju(int framePozicija, int x2, int y2)
	{
		cv::Point p2 = cv::Point(x2, y2);
		if (historijaPozicija->getVelicina() > 2)
		{
			MotionStep* mPoint1 = historijaPozicija->getOlderVersion(25);

			if (mPoint1 != nullptr)
			{
				cv::Point p1 = mPoint1->item;
				int Dx = DeltaX(p1, p2);
				int Dy = DeltaY(p1, p2);
				if (abs(Dy) > 5 || abs(Dx) > 5)
				{
					if (ugaoPravcaKretanja == nullptr)
						ugaoPravcaKretanja = new float;

					if (lastDx == nullptr)
						lastDx = new int;

					if (lastDy == nullptr)
						lastDy = new int;

					*lastDx = Dx;
					*lastDy = Dy;
					*ugaoPravcaKretanja = IzracunajUgao(Dx, Dy);
				}
			}

		}
		historijaPozicija->dodaj(framePozicija, p2);
	}
};
