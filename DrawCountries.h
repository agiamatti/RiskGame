#pragma once

#include <vector>
#include <QGraphicsPolygonItem>
#include "Country.h"


class DrawCountry : public QGraphicsPolygonItem
{
public:
    DrawCountry(vector <Country*> countries, QGraphicsItem* parent = NULL);
};
