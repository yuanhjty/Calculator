#include "CalcButton.h"

CalcButton::CalcButton(QWidget *parent) : QPushButton(parent)
{
	setStyleSheet(
	            "CalcButton {"
	                "background-color: rgb(240, 240, 240);"
	                "border: 0px"
	            "}"

	            "CalcButton:hover {"
	                "background-color: rgb(220, 220, 220);"
	            "}"

	            "CalcButton:pressed {"
	                "background-color: rgb(200, 200, 200);"
	            "}"
	            );
}
