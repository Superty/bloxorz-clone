#include "NumericDisplay.hpp"

const std::vector<int> SevenSegment::litSegments[12] = {
		{0, 1, 2, 4, 5, 6}		// 0
	,	{2, 5}					// 1
	,	{0, 2, 3, 4, 6}			// 2
	,	{0, 2, 3, 5, 6}			// 3
	,	{1, 2, 3, 5}			// 4
	,	{0, 1, 3, 5, 6}			// 5
	,	{0, 1, 3, 4, 5, 6}		// 6
	,	{0, 2, 5}				// 7
	,	{0, 1, 2, 3, 4, 5, 6}	// 8
	,	{0, 1, 2, 3, 5, 6}		// 9
	,	{3}						// -
	,	{}						// (blank)
};

SevenSegment::SevenSegment(vec3 pos, GLfloat stroke, GLfloat side, GLuint sym)
:	symbol(sym)
,	segments({
		Rectangle(pos + vec3(stroke, 2*side + 2*stroke, 0),
			side, stroke)
	,	Rectangle(pos + vec3(0, side + 2*stroke, 0),
			stroke, side)
	,	Rectangle(pos + vec3(stroke + side, side + 2*stroke, 0),
			stroke, side)
	,	Rectangle(pos + vec3(stroke, side + stroke, 0),
			side, stroke)
	,	Rectangle(pos + vec3(0, stroke, 0),
			stroke, side)
	,	Rectangle(pos + vec3(stroke + side, stroke, 0),
			stroke, side)
	,	Rectangle(pos + vec3(stroke, 0, 0),
			side, stroke)
	})
{  }

void SevenSegment::draw() {
	for(auto segmentIndex: litSegments[symbol]) {
		segments[segmentIndex].draw();
	}
}

NumericDisplay::NumericDisplay(vec3 pos, GLuint digitCount, GLfloat stroke, GLfloat side, GLint value)
:	width(digitCount*(3*stroke + side) - stroke)
,	height(3*stroke + 2*side)
{
	pos.x -= width;
	pos.y -= height;
	for(GLuint i = 0; i < digitCount; i++) {
		digitDisplays.push_back(SevenSegment(
			pos + vec3(i*(3*stroke + side), 0, 0),
			stroke,
			side,
			SevenSegment::BLANK
		));
	}
	setValue(value);
}

bool NumericDisplay::setValue(GLint value) {
	if(value == 0) {
		digitDisplays.back().symbol = 0;
		return true;
	}

	bool negative = (value < 0);
	value = abs(value);
	GLint i;
	for(i = digitDisplays.size() - 1; i >= 0 && value > 0; i--) {
		digitDisplays[i].symbol = value % 10;
		value /= 10;
	}

	if(value > 0) {
		return false;
	}

	if(negative) {
		if(i >= 0) {
			digitDisplays[i].symbol = SevenSegment::MINUS;
			i--;
		}
		else {
			return false;
		}
	}

	while(i >= 0) {
		digitDisplays[i].symbol = SevenSegment::BLANK;
		i--;
	}

	return true;
}

void NumericDisplay::draw() {
	for(SevenSegment digitDisplay: digitDisplays) {
		digitDisplay.draw();
	}
}
