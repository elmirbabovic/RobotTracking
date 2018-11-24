#pragma once
#include "Robot.h"
#include "ATP/ListaSekv.h"


class RobotCollector
{
private:
	Lista<Robot*>* roboti = new ListaSekv<Robot*>;
public:

	int Count()
	{
		return roboti->count();
	}

	void RemovedOldRobots(int currentFrame)
	{
		for (int i = 0; i < roboti->count(); ++i)
		{
			Robot* robot = roboti->get(i);
			MotionStep* pozicija_najnovija = robot->GetPozicijaNajnovija();
			if (pozicija_najnovija != nullptr)
			{
				if (currentFrame - pozicija_najnovija->versionNumber > 100)
				{
					robot->Remove();
				}
			}
		}
	}

	void DodajRobota(int framePozicija, int pocetno_x, int pocetno_y, cv::Scalar color)
	{
		Robot* robot = new Robot(roboti->count(), framePozicija, pocetno_x, pocetno_y, color);
		roboti->Add(robot);
	}

	Robot* GetRobotById(int id)
	{
		for (int i = 0; i < roboti->count(); ++i)
		{
			Robot* robot = roboti->get(i);
			if (robot->GetId() == id)
				return robot;
		}
		return nullptr;
	}

	Robot* Find_NajbliziRobot(int x, int y, int maxDisplacement)
	{
		float minUdaljenost = INT_MAX;
		Robot* minRobot = nullptr;
		cv::Point p(x, y);

		for (int i = 0; i < roboti->count(); ++i)
		{
			Robot* currentRobot = roboti->get(i);
			float d = currentRobot->Udaljenost_OdTacke(p);
			if (d<minUdaljenost)
			{
				minUdaljenost = d;
				minRobot = currentRobot;
			}
		}

		if (minUdaljenost < maxDisplacement)
		{
			return minRobot;
		}

		return nullptr;
	}

	Robot* GetRobotByIndex(int i)
	{
		if (i >= roboti->count())
			return 0;
		return roboti->get(i);
	}
};
