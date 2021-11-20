#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>
#include <QString>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();




 // Add you custom slots here

protected:
    void createWidgets();        //Function to create the widgets
    void placeWidget();         // Function to place the widgets
    void makeConnexions();      // Create all the connectivity
private:
    int * left;          //left operand
    int * right;         // right operand
   // QString operation;  // Pointer on the current operation

//events
protected:
   void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events

private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;            // enter button
  QVector<QPushButton*> operations; //operation buttons


     QPushButton *c;                // clear button

    QLCDNumber *disp;             // Where to display the numbers
public slots:
    void changeOperation();  //Slot to handle the click on operations
    void newDigit();
    void Enter();
    void clear();

};
#endif // CALCULATOR_H
