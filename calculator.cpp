#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <QString>





double val = 0;
bool diiv =false;
bool mult=false;
bool add=false;
bool sub =false;
bool cl=false;




Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();


}






Calculator::~Calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}


void Calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0; i < 10; i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());
    }


    //operatiosn buttons
  operations.push_back(new QPushButton("+"));
  operations.push_back(new QPushButton("-"));
  operations.push_back(new QPushButton("*"));
  operations.push_back(new QPushButton("/"));

  // enter button
  enter = new QPushButton("Enter",this);

  // clear button
     c=new QPushButton("C");




    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);





}

void Calculator::placeWidget()
{

    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);


    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);


    //Adding the operations
   for(int i=0; i < 4; i++)
        buttonsLayout->addWidget(operations[ i], i, 4);



    //Adding the 0 button
    buttonsLayout->addWidget(digits[0], 3, 0);
    buttonsLayout->addWidget(enter, 3, 1);
    buttonsLayout->addWidget(c, 3, 2);

    setLayout(layout);
}

void Calculator::makeConnexions()
{

    //Connection of new digit

    for(int i=0; i <10; i++)
        connect(digits[i], &QPushButton::clicked,
                this, &Calculator::newDigit);


    //Connection operations buttons

     for(int i=0; i < 4; i++)
         connect(operations[i],&QPushButton::clicked,
                  this,&Calculator:: changeOperation);

    // connection of enter button
     connect(enter,&QPushButton::clicked,
               this,&Calculator:: Enter);

     //connection of clear button
     connect(c,&QPushButton::clicked,
               this,&Calculator:: clear);


}





void Calculator::newDigit(){

    //Getting the identity of the button using dynamic_cast
    auto button  = dynamic_cast<QPushButton*>(sender());



   //enter  digit
   int digit = ( QString::number(disp->value())+button->text()).toInt(); // we can enter more than 1 digit
   QString new_digit= QString::number(digit,'g',15);  //  the argiment'g' and 15 mean that we can enter a number of 6 digits

    //Displaying the digit
   disp->display(new_digit.toInt());

}

void Calculator::changeOperation()
{

     diiv= false;
     mult= false;
     add= false;
     sub= false;

    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());


    QString dispVal = QString::number(disp->value()) ;
    val=dispVal.toInt();



    // check if the textButton matches the giving sign

    QString buttonVal = button->text();

    //we will compare   each button text with  symbols of operations
    if(QString::compare(buttonVal,"/",Qt::CaseInsensitive)==0){
        diiv = true;
    }
    if(QString::compare(buttonVal, "*",Qt::CaseInsensitive)==0){
        mult=true;
    }
        if(QString::compare(buttonVal, "+",Qt::CaseInsensitive)==0){
       add=true;
    }
        if(QString::compare(buttonVal, "-",Qt::CaseInsensitive)==0) {
       sub=true;
   }


 disp->display("");

    }

void Calculator::Enter(){



     double solution = 0;
     QString displayVal = QString::number(disp->value()) ;
    int dbDisplayVal = displayVal.toInt();

    //make operations

     if(add || sub || mult || diiv){
         if(add){
         solution = val + dbDisplayVal;
     } else if (sub){
         solution = val - dbDisplayVal;
     } else if (mult){
         solution = val * dbDisplayVal;
     }else {
            solution = val / dbDisplayVal;
         }

}
     disp->display(solution);




}


void Calculator::clear(){

       disp->display("0");



}
void Calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);



}


