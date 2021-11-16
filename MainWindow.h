#ifndef MAINWINDOW_H
#define MAINW INDOW_H

#include <QMainWindow>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow* ui;

	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<QVTKInteractor> mInteractor;
	vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;

	
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	
public slots:
	
	void Browsefile();
	auto OpenDICOM(std::string x);
	auto OpenDICOM2(std::string x);
	auto OpenDICOM3(std::string x);
	auto OpenDICOM11(std::string x);
	auto OpenDICOM12(std::string x);
	auto OpenDICOM21(std::string x);
	auto OpenDICOM22(std::string x);
	auto OpenDICOM31(std::string x);
	auto OpenDICOM32(std::string x);
    void MoveForward();
	void Volume(std::string x, int y);
	void MIP();
	void bone();
	void skin();
	void muscle();
	auto threshold(std::string x);
	//void MoveSlicesForward();


};

#endif // MAINWINDOW_H