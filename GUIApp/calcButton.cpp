#include "CalcButton.h"

CalcButton::CalcButton(QWidget *parent) : QPushButton(parent)
{
	setStyleSheet(
	            "CalcButton {"
	                "background-color: rgb(255, 255, 255);"
	                "border: 0px"
	            "}"

	            "CalcButton:hover {"
	                "background-color: rgb(225, 225, 225);"
	            "}"

	            "CalcButton:pressed {"
	                "background-color: rgb(200, 200, 200);"
	            "}"
	            );
}
