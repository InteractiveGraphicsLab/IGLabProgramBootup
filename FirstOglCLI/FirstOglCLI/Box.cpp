﻿#include "pch.h"
#include "Box.h"
#include "OglForCLI.h"

Box::Box()
{

}

Box::~Box()
{

}

void Box::setMax(EVec3f max)
{
	max_ = max;
}

void Box::setMin(EVec3f min)
{
	min_ = min;
}

EVec3f Box::getMax() const
{
	return max_;
}

EVec3f Box::getMin() const
{
	return min_;
}

void Box::Draw()
{

	glLineWidth(2.0f);
	glDisable(GL_LIGHTING);//“d‹C‚ðÁ‚·

	glBegin(GL_LINES);
	glColor3d(1, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, 0, max_[2]);
	glColor3d(1, 0, 1); glVertex3d(0, 0, 0); glVertex3d(0, max_[1], 0);
	glColor3d(1, 0, 1); glVertex3d(0, 0, 0); glVertex3d(max_[0], 0, 0);
	glColor3d(1, 0, 1); glVertex3d(max_[0], 0, max_[2]); glVertex3d(0, 0, max_[2]);
	glColor3d(1, 0, 1); glVertex3d(max_[0], 0, max_[2]); glVertex3d(max_[0], 0, 0);
	glColor3d(1, 0, 1); glVertex3d(max_[0], 0, max_[2]); glVertex3d(max_[0], max_[1], max_[2]);
	glColor3d(1, 0, 1); glVertex3d(0, max_[1], max_[2]); glVertex3d(0, max_[1], 0);
	glColor3d(1, 0, 1); glVertex3d(0, max_[1], max_[2]); glVertex3d(0, 0, max_[2]);
	glColor3d(1, 0, 1); glVertex3d(0, max_[1], max_[2]); glVertex3d(max_[0], max_[1], max_[2]);
	glColor3d(1, 0, 1); glVertex3d(max_[0], max_[1], 0); glVertex3d(0, max_[1], 0);
	glColor3d(1, 0, 1); glVertex3d(max_[0], max_[1], 0); glVertex3d(max_[0], 0, 0);
	glColor3d(1, 0, 1); glVertex3d(max_[0], max_[1], 0); glVertex3d(max_[0], max_[1], max_[2]);
	glEnd();


	/*
	glBegin(GL_QUAD_STRIP);
	glColor3b(0, 1, 0);
	//sx0
	glVertex3d(0,       0,       0      );
	glVertex3d(0,       0,       max_[2]);
	glVertex3d(0,       max_[1], 0      );
	glVertex3d(0,       max_[1], max_[2]);
	//sx1
	glVertex3d(max_[0], 0,       0      );
	glVertex3d(max_[0], 0,       max_[2]);
	glVertex3d(max_[0], max_[1], 0      );
	glVertex3d(max_[0], max_[1], max_[2]);
	//sy0
	glVertex3d(0,       0,       0      );
	glVertex3d(max_[0], 0,       0      );
	glVertex3d(0,       0,       max_[2]);
	glVertex3d(max_[0], 0,       max_[2]);
	//sy1
	glVertex3d(0,       max_[1], 0      );
	glVertex3d(max_[0], max_[1], 0      );
	glVertex3d(0,       max_[1], max_[2]);
	glVertex3d(max_[0], max_[1], max_[2]);
	//sz0
	glVertex3d(0,       0,       0      );
	glVertex3d(max_[0], 0,       0      );
	glVertex3d(0,       max_[1], 0      );
	glVertex3d(max_[0], max_[1], 0      );
	//sz1
	glVertex3d(0, 0, max_[2]);
	glVertex3d(max_[0], 0,       max_[2]);
	glVertex3d(0,       max_[1], max_[2]);
	glVertex3d(max_[0], max_[1], max_[2]);

	glEnd();*/
}