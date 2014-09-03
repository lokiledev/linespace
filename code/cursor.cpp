#include "cursor.h"

const GLfloat Cursor::colors_[5][4] = {
    {1.0, 1.0, 1.0, 0.8},
    {0.0, 0.0, 0.0, 1.0},
    {1.0, 0.0, 0.0, 0.7},
    {0.0, 1.0, 0.0, 0.7},
    {0.0, 0.0, 1.0, 0.7},
};

Cursor::Cursor(QObject *parent) :
    QObject(parent),
    pos_(Leap::Vector()),
    state_(Cursor::IDLE),
    size_(0.02f),
    sensitivity_(2.0f)
{
}

const GLfloat* Cursor::getColorFromState() const{
    return colors_[state_];
}

const Leap::Vector Cursor::getPos() const{
    return pos_;
}

float Cursor::getSize() const{
    return size_;
}

//update position from normalized leap unit box to our coordinate space
void Cursor::slotMove(const Leap::Vector& pos){
    //Leap normalized is in range [0..1]
    //we want to center on 0,0 and Z in range [-1, 0]
    Leap::Vector offset(-0.5f, -0.5f, -1.0f);
    pos_ = (pos + offset)*sensitivity_;
}

void Cursor::slotChangeState(Cursor::CursorState_e state){
    state_ = state;
}
