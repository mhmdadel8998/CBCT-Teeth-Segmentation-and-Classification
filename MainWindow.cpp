#include "MainWindow.h"

#include "ui_MainWindow.h"

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkNamedColors.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <windows.h>
#include <vtkDataArray.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <QVTKOpenGLWidget.h>
#include <vtkImageGaussianSmooth.h>
#include <vtkDirectory.h>
#include <QDir>
#include <vtkInteractorStyleImage.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <sstream>
#include <vtkActor2D.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkActor.h>
#include <vtkImageCast.h>
#include <vtkImageData.h>
#include <vtkImageMapper3D.h>
#include <vtkImageNoiseSource.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include < vtkImageHistogram.h >
#include <vtkCamera.h>
#include <vtkColorTransferFunction.h>
#include <vtkCommand.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkImageResample.h>
#include <vtkMetaImageReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlanes.h>
#include <vtkProperty.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkXMLImageDataReader.h>
#include <vtkImageFlip.h>
#include <vtkImageCast.h>
#include <vtkImageMedian3D.h>
#include <vtkImageThreshold.h>
#include <vtkImageActor.h>

std::string inputfilename;


MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New())
	
{
	ui->setupUi(this);

	// Set up the rendering
	mRenderWindow->AddRenderer(mRenderer);
	mRenderWindow->SetInteractor(mInteractor);
	ui->openGLWidget->SetRenderWindow(mRenderWindow);
	mInteractor->SetInteractorStyle(mInteractorStyle);
	mInteractor->Initialize();
	
	// Set the UI connections
	QObject::connect(ui->actionOpen, &QAction::triggered,
		this, &MainWindow::Browsefile);
   // QObject::connect(ui->actionrotate, &QAction::triggered,
     //   this, &MainWindow::MoveSlicesForward);
    QObject::connect(ui->actionMIP, &QAction::triggered,
        this, &MainWindow::MIP);
    QObject::connect(ui->actionSkin, &QAction::triggered,
        this, &MainWindow::skin);
    QObject::connect(ui->actionMuscle, &QAction::triggered,
        this, &MainWindow::muscle);
    QObject::connect(ui->actionBone, &QAction::triggered,
        this, &MainWindow::bone);
    

}

MainWindow::~MainWindow() {
	delete ui;
}

class StatusMessage
{
public:
    static std::string Format(int slice, int maxSlice)
    {
        std::stringstream tmp;
        tmp << "Slice Number  " << slice + 1 << "/" << maxSlice + 1;
        return tmp.str();
    }
};

// Define own interaction style
class myVtkInteractorStyleImage : public vtkInteractorStyleImage
{
public:
    static myVtkInteractorStyleImage* New();
    vtkTypeMacro(myVtkInteractorStyleImage, vtkInteractorStyleImage);

protected:
    vtkImageViewer2* _ImageViewer;
    vtkTextMapper* _StatusMapper;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;

public:
    void SetImageViewer(vtkImageViewer2* imageViewer)
    {
        _ImageViewer = imageViewer;
        _MinSlice = imageViewer->GetSliceMin();
        _MaxSlice = imageViewer->GetSliceMax();
        _Slice = _MinSlice;
        cout << "Slicer: Min = " << _MinSlice << ", Max = " << _MaxSlice
            << std::endl;

    }

    void SetStatusMapper(vtkTextMapper* statusMapper)
    {
        _StatusMapper = statusMapper;
    }

public:
    void MoveSliceForward()
    {
        if (_Slice < _MaxSlice)
        {
            _Slice += 1;
            cout << "MoveSliceForward::Slice = " << _Slice << std::endl;
            _ImageViewer->SetSlice(_Slice);
            std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
            _StatusMapper->SetInput(msg.c_str());
            _ImageViewer->Render();
        }
    }

    void  MoveSliceBackward()
    {

        if (_Slice > _MinSlice)
        {
            _Slice -= 1;
            cout << "MoveSliceBackward::Slice = " << _Slice << std::endl;
            _ImageViewer->SetSlice(_Slice);
            std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
            _StatusMapper->SetInput(msg.c_str());
            _ImageViewer->Render();
        }
    }

    virtual void OnKeyDown()
    {
        std::string key = this->GetInteractor()->GetKeySym();
        if (key.compare("Up") == 0)
        {
            // cout << "Up arrow key was pressed." << endl;
            MoveSliceForward();
        }
        else if (key.compare("Down") == 0)
        {
            // cout << "Down arrow key was pressed." << endl;
            MoveSliceBackward();
        }
        // forward event
        vtkInteractorStyleImage::OnKeyDown();
    }

    virtual void OnMouseWheelForward()
    {
        // std::cout << "Scrolled mouse wheel forward." << std::endl;
        MoveSliceForward();
    }

    virtual void OnMouseWheelBackward()
    {
        // std::cout << "Scrolled mouse wheel backward." << std::endl;
        if (_Slice > _MinSlice)
        {
            MoveSliceBackward();
        }
    }
};

vtkStandardNewMacro(myVtkInteractorStyleImage);

void MainWindow::MoveForward()
{
    /*
   //yVtkInteractorStyleImage *r;
    r->MoveSliceForward();
    //std::cout << "mo";
    */
}
/*
void MainWindow::MoveSlicesForward()
{
    vtkImageViewer2* _ImageViewer;
    vtkTextMapper* _StatusMapper;
    int _Slice;
    int _MinSlice;
    int _MaxSlice;
    if (_Slice < _MaxSlice)
    {
        _Slice += 1;
        cout << "MoveSliceForward::Slice = " << _Slice << std::endl;
        _ImageViewer->SetSlice(_Slice);
        std::string msg = StatusMessage::Format(_Slice, _MaxSlice);
        _StatusMapper->SetInput(msg.c_str());
        _ImageViewer->Render();
    }
}
*/
void MainWindow::Volume(std::string x, int y) {


    int count = 1;
    double opacityWindow = 4096;
    double opacityLevel = 2048;
    int blendType = y;
    int clip = 0;
    double reductionFactor = 1.0;
    double frameRate = 10.0;

    bool independentComponents = true;
    // Create the renderer, render window and interactor
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(renderer);


    vtkNew<vtkRenderWindowInteractor> iren;
    iren->SetRenderWindow(renWin);
    iren->SetDesiredUpdateRate(frameRate / (1 + clip));

    iren->GetInteractorStyle()->SetDefaultRenderer(renderer);

    // Read the data
    vtkSmartPointer<vtkAlgorithm> reader;
    vtkSmartPointer<vtkImageData> input;
   
        vtkNew<vtkDICOMImageReader> dicomReader;
        dicomReader->SetDirectoryName(x.c_str());
        dicomReader->Update();
        input = dicomReader->GetOutput();
        reader = dicomReader;
    

    // Verify that we actually have a volume
    int dim[3];
    input->GetDimensions(dim);

    if (dim[0] < 2 || dim[1] < 2 || dim[2] < 2)
    {
        cout << "Error loading data!" << endl;
        exit(EXIT_FAILURE);
    }

    vtkNew<vtkImageResample> resample;
    if (reductionFactor < 1.0)
    {
        resample->SetInputConnection(reader->GetOutputPort());
        resample->SetAxisMagnificationFactor(0, reductionFactor);
        resample->SetAxisMagnificationFactor(1, reductionFactor);
        resample->SetAxisMagnificationFactor(2, reductionFactor);
    }

    // Create our volume and mapper
    vtkNew<vtkVolume> volume;
    vtkNew<vtkFixedPointVolumeRayCastMapper> mapper;

    if (reductionFactor < 1.0)
    {
        mapper->SetInputConnection(resample->GetOutputPort());
    }
    else
    {
        mapper->SetInputConnection(reader->GetOutputPort());
    }

    // Set the sample distance on the ray to be 1/2 the average spacing
    double spacing[3];
    if (reductionFactor < 1.0)
    {
        resample->GetOutput()->GetSpacing(spacing);
    }
    else
    {
        input->GetSpacing(spacing);
    }

    // Create our transfer function
    vtkNew<vtkColorTransferFunction> colorFun;
    vtkNew<vtkPiecewiseFunction> opacityFun;
    // Create the property and attach the transfer functions
    vtkNew<vtkVolumeProperty> property;
    property->SetIndependentComponents(independentComponents);
    property->SetColor(colorFun);
    property->SetScalarOpacity(opacityFun);
    property->SetInterpolationTypeToLinear();

    // connect up the volume to the property and the mapper
    volume->SetProperty(property);
    volume->SetMapper(mapper);

    // Depending on the blend type selected as a command line option,
    // adjust the transfer function
    switch (blendType)
    {
        // MIP
        // Create an opacity ramp from the window and level values.
        // Color is white. Blending is MIP.
    case 0:
        colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(opacityLevel - 0.5 * opacityWindow, 0.0,
            opacityLevel + 0.5 * opacityWindow, 1.0);
        mapper->SetBlendModeToMaximumIntensity();
        break;
        // CompositeRamp
    // Create a ramp from the window and level values. Use compositing
    // without shading. Color is a ramp from black to white.
    case 1:
        colorFun->AddRGBSegment(opacityLevel - 0.5 * opacityWindow, 0.0, 0.0, 0.0,
            opacityLevel + 0.5 * opacityWindow, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(opacityLevel - 0.5 * opacityWindow, 0.0,
            opacityLevel + 0.5 * opacityWindow, 1.0);
        mapper->SetBlendModeToComposite();
        property->ShadeOff();
        break;

        // CompositeShadeRamp
        // Create a ramp from the window and level values. Use compositing
        // with shading. Color is white.
    case 2:
        colorFun->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
        opacityFun->AddSegment(opacityLevel - 0.5 * opacityWindow, 0.0,
            opacityLevel + 0.5 * opacityWindow, 1.0);
        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        break;

        // CT_Skin
        // Use compositing and functions set to highlight skin in CT data
        // Not for use on RGB data
    case 3:
        colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
        colorFun->AddRGBPoint(-1000, .62, .36, .18, 0.5, 0.0);
        colorFun->AddRGBPoint(-500, .88, .60, .29, 0.33, 0.45);
        colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

        opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
        opacityFun->AddPoint(-1000, 0, 0.5, 0.0);
        opacityFun->AddPoint(-500, 1.0, 0.33, 0.45);
        opacityFun->AddPoint(3071, 1.0, 0.5, 0.0);

        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetSpecular(0.2);
        property->SetSpecularPower(10.0);
        property->SetScalarOpacityUnitDistance(0.8919);
        break;

        // CT_Bone
        // Use compositing and functions set to highlight bone in CT data
        // Not for use on RGB data
    case 4:
        colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
        colorFun->AddRGBPoint(-16, 0.73, 0.25, 0.30, 0.49, .61);
        colorFun->AddRGBPoint(641, .90, .82, .56, .5, 0.0);
        colorFun->AddRGBPoint(3071, 1, 1, 1, .5, 0.0);

        opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
        opacityFun->AddPoint(-16, 0, .49, .61);
        opacityFun->AddPoint(641, .72, .5, 0.0);
        opacityFun->AddPoint(3071, .71, 0.5, 0.0);

        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetSpecular(0.2);
        property->SetSpecularPower(10.0);
        property->SetScalarOpacityUnitDistance(0.8919);
        break;

        // CT_Muscle
        // Use compositing and functions set to highlight muscle in CT data
        // Not for use on RGB data
    case 5:
        colorFun->AddRGBPoint(-3024, 0, 0, 0, 0.5, 0.0);
        colorFun->AddRGBPoint(-155, .55, .25, .15, 0.5, .92);
        colorFun->AddRGBPoint(217, .88, .60, .29, 0.33, 0.45);
        colorFun->AddRGBPoint(420, 1, .94, .95, 0.5, 0.0);
        colorFun->AddRGBPoint(3071, .83, .66, 1, 0.5, 0.0);

        opacityFun->AddPoint(-3024, 0, 0.5, 0.0);
        opacityFun->AddPoint(-155, 0, 0.5, 0.92);
        opacityFun->AddPoint(217, .68, 0.33, 0.45);
        opacityFun->AddPoint(420, .83, 0.5, 0.0);
        opacityFun->AddPoint(3071, .80, 0.5, 0.0);

        mapper->SetBlendModeToComposite();
        property->ShadeOn();
        property->SetAmbient(0.1);
        property->SetDiffuse(0.9);
        property->SetSpecular(0.2);
        property->SetSpecularPower(10.0);
        property->SetScalarOpacityUnitDistance(0.8919);
        break;

        // RGB_Composite
        // Use compositing and functions set to highlight red/green/blue regions
        // in RGB data. Not for use on single component data
    case 6:
        opacityFun->AddPoint(0, 0.0);
        opacityFun->AddPoint(5.0, 0.0);
        opacityFun->AddPoint(30.0, 0.05);
        opacityFun->AddPoint(31.0, 0.0);
        opacityFun->AddPoint(90.0, 0.0);
        opacityFun->AddPoint(100.0, 0.3);
        opacityFun->AddPoint(110.0, 0.0);
        opacityFun->AddPoint(190.0, 0.0);
        opacityFun->AddPoint(200.0, 0.4);
        opacityFun->AddPoint(210.0, 0.0);
        opacityFun->AddPoint(245.0, 0.0);
        opacityFun->AddPoint(255.0, 0.5);

        mapper->SetBlendModeToComposite();
        property->ShadeOff();
        property->SetScalarOpacityUnitDistance(1.0);
        break;
    default:
        vtkGenericWarningMacro("Unknown blend type.");
        break;
    }

    // Set the default window size

    renWin->SetSize(800, 800);
    //renWin->SetSharedRenderWindow(ui->openGLWidget_10->GetRenderWindow());
    renWin->SetWindowName("MIP Volume");
    renWin->Render();

    // Add the volume to the scene
    renderer->AddVolume(volume);
    // renderer->SetRenderWindow(ui->openGLWidget_10->GetRenderWindow());
    renderer->ResetCamera();
    //renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
    /*
    auto camera = renderer->GetActiveCamera();

    camera->SetPosition(56.8656, -297.084, 78.913);
    camera->SetFocalPoint(109.139, 120.604, 63.5486);
    camera->SetViewUp(-0.00782421, -0.0357807, -0.999329);
    camera->SetDistance(421.227);
    camera->SetClippingRange(146.564, 767.987);
    */
    //renWin->SetSharedRenderWindow(ui->openGLWidget_10->GetRenderWindow());
    // interact with data
    renWin->Render();

    iren->Start();
    //return EXIT_SUCCESS;
}

auto MainWindow::OpenDICOM32(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageMedian3D> median;
    median->SetInputConnection(reader->GetOutputPort());
    median->SetKernelSize(7, 7, 7);


    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(median->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        "Filtered Median Coronal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    // imageViewer->GetRenderer()->SetBackground(
         //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_9->GetRenderWindow());
    imageViewer->SetSliceOrientationToXZ();
    imageViewer->Render();
    Volume(x , 0);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;

}

void MainWindow::MIP() {

    Volume("E:/Data/128602 - L  yz/CT", 0);
}


void MainWindow::bone() {
 
    Volume("E:/Data/128602 - L  yz/CT", 4);
}

void MainWindow::skin() {

    Volume("E:/Data/128602 - L  yz/CT", 3);
}

void MainWindow::muscle() {

    Volume("E:/Data/128602 - L  yz/CT", 5);
}

auto MainWindow::OpenDICOM31(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageCast> cast;
    cast->SetInputConnection(reader->GetOutputPort());
    cast->SetOutputScalarTypeToFloat();

    vtkNew<vtkImageGaussianSmooth> filter;
    filter->SetDimensionality(2);
    filter->SetInputConnection(cast->GetOutputPort());
    filter->SetStandardDeviations(4.0, 4.0);
    filter->SetRadiusFactors(2.0, 2.0);



    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(filter->GetOutputPort());


    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Filtered Gaussian Coronal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    //imageViewer->GetRenderer()->SetBackground(
        //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_6->GetRenderWindow());
    imageViewer->SetSliceOrientationToXZ();
    imageViewer->Render();
    OpenDICOM32(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;


}


auto MainWindow::OpenDICOM3(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();

    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(reader->GetOutputPort());


    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Coronal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    //imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
   // imageViewer->GetRenderer()->SetBackground(
      //  colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->Render();
    imageViewer->SetSliceOrientationToXZ();
    imageViewer->SetRenderWindow(ui->openGLWidget_3->GetRenderWindow());
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    //Volume(x);
    OpenDICOM31(x);
    renderWindowInteractor->Start();

    return 0;
    return EXIT_SUCCESS;
}

auto MainWindow::OpenDICOM22(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageMedian3D> median;
    median->SetInputConnection(reader->GetOutputPort());
    median->SetKernelSize(7, 7, 7);


    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(median->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        "Filtered Median Sagittal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    // imageViewer->GetRenderer()->SetBackground(
         //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_8->GetRenderWindow());
    imageViewer->SetSliceOrientationToYZ();
    imageViewer->Render();
    OpenDICOM3(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;

}

auto MainWindow::OpenDICOM21(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageCast> cast;
    cast->SetInputConnection(reader->GetOutputPort());
    cast->SetOutputScalarTypeToFloat();

    vtkNew<vtkImageGaussianSmooth> filter;
    filter->SetDimensionality(2);
    filter->SetInputConnection(cast->GetOutputPort());
    filter->SetStandardDeviations(4.0, 4.0);
    filter->SetRadiusFactors(2.0, 2.0);



    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(filter->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Filtered Gaussian Sagittal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    //imageViewer->GetRenderer()->SetBackground(
        //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_5->GetRenderWindow());
    imageViewer->SetSliceOrientationToYZ();
    imageViewer->Render();
    OpenDICOM22(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;


}

auto MainWindow::OpenDICOM2(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();

    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(reader->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Sagittal "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    //imageViewer->GetRenderer()->SetBackground(
        //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(1000, 1000);
    //imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_2->GetRenderWindow());
    imageViewer->SetSliceOrientationToYZ();
    imageViewer->Render();
    OpenDICOM21(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();
    return 0;
    return EXIT_SUCCESS;
}

auto MainWindow::OpenDICOM12(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageMedian3D> median;
    median->SetInputConnection(reader->GetOutputPort());
    median->SetKernelSize(7, 7, 7);


    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(median->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        "Filtered Median Axial "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    // imageViewer->GetRenderer()->SetBackground(
         //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_7->GetRenderWindow());
    imageViewer->Render();
    OpenDICOM2(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;
    
}

auto MainWindow::OpenDICOM11(std::string x) {

    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();
    vtkNew<vtkImageCast> cast;
    cast->SetInputConnection(reader->GetOutputPort());
    cast->SetOutputScalarTypeToFloat();

    vtkNew<vtkImageGaussianSmooth> filter;
    filter->SetDimensionality(2);
    filter->SetInputConnection(cast->GetOutputPort());
    filter->SetStandardDeviations(4.0, 4.0);
    filter->SetRadiusFactors(2.0, 2.0);
 


    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(filter->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Filtered Gaussian Axial "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);


    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
    //imageViewer->GetRenderer()->SetBackground(
        //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    imageViewer->SetRenderWindow(ui->openGLWidget_4->GetRenderWindow());
    imageViewer->Render();
    OpenDICOM12(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    return EXIT_SUCCESS;


}

auto MainWindow::threshold(std::string x) {
    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
    reader->SetDirectoryName(folder.c_str());
    reader->Update();

    vtkNew<vtkImageThreshold> imageThreshold;
    imageThreshold->SetInputConnection(reader->GetOutputPort());
    unsigned char lower = 3496;
    unsigned char upper = 3497;
    imageThreshold->ThresholdBetween(lower, upper);
   // imageThreshold->ThresholdByLower(upper);
    imageThreshold->ReplaceInOn();
    imageThreshold->SetInValue(151);
    //imageThreshold->ReplaceOutOn();
   // imageThreshold->SetOutValue(151);
    imageThreshold->Update();
    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(imageThreshold->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
        // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Axial "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);

    // initialize rendering and interaction

    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    //imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    //imageViewer->SetColorWindow(range[1] - range[0]);
    // imageViewer->GetRenderer()->SetBackground(
         //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    //imageViewer->SetRenderWindow(ui->openGLWidget->GetRenderWindow());
    imageViewer->Render();
    OpenDICOM11(x);
    //threshold(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();

    // Create actors
    //vtkNew<vtkImageActor> inputActor;
    //inputActor->GetMapper()->SetInputConnection(imageThreshold->GetOutputPort());
/*
    vtkNew<vtkImageActor> thresholdedActor;
    thresholdedActor->GetMapper()->SetInputConnection(
        imageThreshold->GetOutputPort());

    // There will be one render window
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(600, 300);
    renderWindow->SetWindowName("ImageThreshold");

    // And one interactor
    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    // Define viewport ranges
    // (xmin, ymin, xmax, ymax)
    
    double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
    double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

    // Setup both renderers
    vtkNew<vtkRenderer> leftRenderer;
    renderWindow->AddRenderer(leftRenderer);
    leftRenderer->SetViewport(leftViewport);
    leftRenderer->SetBackground(.6, .5, .4);
    leftRenderer->SetBackground(colors->GetColor3d("Sienna").GetData());

    vtkNew<vtkRenderer> rightRenderer;
    renderWindow->AddRenderer(rightRenderer);
    rightRenderer->SetViewport(rightViewport);
    rightRenderer->SetBackground(.4, .5, .6);
    rightRenderer->SetBackground(colors->GetColor3d("RoyalBlue").GetData());

    leftRenderer->AddActor(inputActor);
    rightRenderer->AddActor(thresholdedActor);
    
    leftRenderer->ResetCamera();
    rightRenderer->ResetCamera();
    
    //renderWindow->AddRenderer(leftRenderer);
   // rightRenderer->AddActor(thresholdedActor);
    vtkNew<vtkRenderer> rightRenderer;
    renderWindow->AddRenderer(rightRenderer);
    rightRenderer->AddActor(thresholdedActor);
    rightRenderer->ResetCamera();
    
    renderWindow->Render();
    OpenDICOM11(x);
    interactor->Start();
    */
    return EXIT_SUCCESS;



}

auto MainWindow::OpenDICOM(std::string x) {
    
    vtkNew<vtkNamedColors> colors;

    std::string folder = x;
    vtkNew<vtkDICOMImageReader> reader;
	reader->SetDirectoryName(folder.c_str());
	reader->Update();
    
    vtkNew<vtkImageViewer2> imageViewer;
    imageViewer->SetInputConnection(reader->GetOutputPort());

    // slice status message
    vtkNew<vtkTextProperty> sliceTextProp;
    sliceTextProp->SetFontFamilyToCourier();
    sliceTextProp->SetFontSize(20);
    sliceTextProp->SetVerticalJustificationToBottom();
    sliceTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> sliceTextMapper;
    std::string msg = StatusMessage::Format(imageViewer->GetSliceMin(),
        imageViewer->GetSliceMax());
    sliceTextMapper->SetInput(msg.c_str());
    sliceTextMapper->SetTextProperty(sliceTextProp);

    vtkNew<vtkActor2D> sliceTextActor;
    sliceTextActor->SetMapper(sliceTextMapper);
    sliceTextActor->SetPosition(15, 10);

    // usage hint message
    vtkNew<vtkTextProperty> usageTextProp;
    usageTextProp->SetFontFamilyToCourier();
    usageTextProp->SetFontSize(14);
    usageTextProp->SetVerticalJustificationToTop();
    usageTextProp->SetJustificationToLeft();

    vtkNew<vtkTextMapper> usageTextMapper;
    usageTextMapper->SetInput(
       // "- Slice with mouse wheel\n  or Up/Down-Key\n- Zoom with pressed right\n "
        " Axial "
    );
    usageTextMapper->SetTextProperty(usageTextProp);

    vtkNew<vtkActor2D> usageTextActor;
    usageTextActor->SetMapper(usageTextMapper);
    usageTextActor->GetPositionCoordinate()
        ->SetCoordinateSystemToNormalizedDisplay();
    usageTextActor->GetPositionCoordinate()->SetValue(0.05, 0.95);

    // create an interactor with our own style (inherit from
    // vtkInteractorStyleImage) in order to catch mousewheel and key events
    vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;

    vtkNew<myVtkInteractorStyleImage> myInteractorStyle;

    // make imageviewer2 and sliceTextMapper visible to our interactorstyle
    // to enable slice status message updates when scrolling through the slices
    myInteractorStyle->SetImageViewer(imageViewer);
    myInteractorStyle->SetStatusMapper(sliceTextMapper);

    imageViewer->SetupInteractor(renderWindowInteractor);
    // make the interactor use our own interactorstyle
    // cause SetupInteractor() is defining it's own default interatorstyle
    // this must be called after SetupInteractor()
    renderWindowInteractor->SetInteractorStyle(myInteractorStyle);
    // add slice status message and usage hint message to the renderer
    imageViewer->GetRenderer()->AddActor2D(sliceTextActor);
    imageViewer->GetRenderer()->AddActor2D(usageTextActor);

    // initialize rendering and interaction
    
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    auto image = reader->GetOutput();
    double* range = image->GetPointData()->GetScalars()->GetRange();
    imageViewer->SetColorLevel(0.5 * (range[0] + range[1]));
    imageViewer->SetColorWindow(range[1] - range[0]);
   // imageViewer->GetRenderer()->SetBackground(
        //colors->GetColor3d("SlateGray").GetData());
    imageViewer->GetRenderWindow()->SetSize(800, 800);
    imageViewer->GetRenderWindow()->SetWindowName("ReadDICOMSeries");
    //imageViewer->SetRenderWindow(ui->openGLWidget->GetRenderWindow());
    imageViewer->Render();
//    OpenDICOM11(x);
    threshold(x);
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();
    renderWindowInteractor->Start();
    

    return EXIT_SUCCESS;
   
}

void MainWindow::Browsefile() {

	QString filename = QFileDialog::getExistingDirectory(this, "Choose File");
	std::string inputfilename = filename.toStdString();
	OpenDICOM(inputfilename);    
}
