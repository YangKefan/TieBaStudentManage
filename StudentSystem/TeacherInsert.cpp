#include "TeacherInsert.h"
#include "ui_TeacherInsert.h"
#include "GBK.h"

TeacherInsert::TeacherInsert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherInsert)
{
    ui->setupUi(this);
    //创建model实现与数据库交互
    model=new QSqlTableModel(this);
    model->setTable("student");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->removeColumns(5,5);
    //设置lineedit提示字段
    ui->numline->setPlaceholderText(GBK::a2w("请输入学生学号"));
    ui->nameline->setPlaceholderText(GBK::a2w("请输入学生姓名"));
    ui->chineseline->setPlaceholderText(GBK::a2w("请输入学生语文成绩"));
    ui->mathline->setPlaceholderText(GBK::a2w("请输入学生数学成绩"));
    ui->englishline->setPlaceholderText(GBK::a2w("请输入学生英语成绩"));
    //设置按钮的图标
    ui->confirmbtn->setIcon(QIcon(":/StudentSystem/img/m10.png"));
    ui->confirmbtn->setFlat(true);
    ui->returnbtn->setIcon(QIcon(":/StudentSystem/img/m11.png"));
    ui->returnbtn->setFlat(true);
    //两个按钮连接信号和槽
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(confirmbtnSlot()));

}

TeacherInsert::~TeacherInsert()
{
    delete ui;
}
void TeacherInsert::clearAll()
{
    ui->numline->clear();
    ui->nameline->clear();
    ui->chineseline->clear();
    ui->mathline->clear();
    ui->englishline->clear();
}
bool TeacherInsert::judgeEmpty()
{
    if(ui->numline->text().isEmpty())
    {
        QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("学生学号不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->nameline->text().isEmpty())
    {
        QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("学生姓名不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->chineseline->text().isEmpty())
    {
        QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("语文成绩不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->mathline->text().isEmpty())
    {
        QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("数学成绩不能为空"),QMessageBox::Yes);
        return false;
    }
    else if(ui->englishline->text().isEmpty())
    {
        QMessageBox::warning(this,GBK::a2w("警告"),GBK::a2w("英语成绩不能为空"),QMessageBox::Yes);
        return false;
    }
    else
        return true;
}
void TeacherInsert::returnbtnSlot()
{
    if(ui->numline->text().isEmpty()&&ui->nameline->text().isEmpty()&&
       ui->chineseline->text().isEmpty()&&ui->mathline->text().isEmpty()&&
       ui->englishline->text().isEmpty())
    {
        emit EmitToTeacherManage();
        this->hide();
        return;
    }
    if(QMessageBox::question(this,GBK::a2w("提示"),GBK::a2w("尚未保存，是否退出"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        emit EmitToTeacherManage();
        this->hide();
    }
}
void TeacherInsert::confirmbtnSlot()
{
    if(!this->judgeEmpty())
        return;
    model->select();
    int i;
    for(i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,0)).toString()==ui->numline->text())
        {
            break;
        }
    }
    if(i!=model->rowCount())
    {
        QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("学生用户已经存在"),QMessageBox::Yes);
        this->clearAll();
        return;
    }
    QSqlRecord record=model->record();
    record.setValue("studentnum",ui->numline->text());
    record.setValue("name",ui->nameline->text());
    record.setValue("chinese",ui->chineseline->text().toFloat());
    record.setValue("math",ui->mathline->text().toFloat());
    record.setValue("english",ui->englishline->text().toFloat());
    model->insertRecord(-1,record);
    if(model->submitAll())
    {
        QMessageBox::information(this,GBK::a2w("提示"),GBK::a2w("学生成绩添加成功"),QMessageBox::Yes);
        this->clearAll();
    }
}
