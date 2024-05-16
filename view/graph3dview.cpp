#include "graph3dview.h"

Graph3DView::Graph3DView(QWidget *parent): QWidget{parent} {
    Data::getInstance().subscribe(this);
    this->_controller = new Graph3DController();

    // Widget and layouts
    auto *mainLayout = new QHBoxLayout;
    auto *surfaceLayout = new QVBoxLayout;

    surfaceLayout->setContentsMargins(0, 0, 5, 0);
    mainLayout->setSpacing(0);

    // Setup the surface
    _surface = new Q3DSurface();
    this->_surface->setMinimumSize(QSize(512, 512));
    this->_surface->setResizeMode(QQuickWidget::SizeRootObjectToView);
    this->_surface->activeTheme()->setType(Q3DTheme::ThemePrimaryColors);
    this->_surface->activeTheme()->setLabelsEnabled(true);
    this->_surface->activeTheme()->setLabelBorderEnabled(false);
    this->_surface->activeTheme()->setGridEnabled(false);
    this->_surface->addSeries(this->_controller->getSeries());

    // Construct the panel layout
    auto *panelContainer = new QWidget; // Container widget for panelLayout
    auto *panelLayout = new QVBoxLayout(panelContainer); // Set panelContainer as the parent
    auto *graphLabel = new QLabel("Graph 3D of the expression");
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setMargin(10);
    QFont font = graphLabel->font();
    font.setPointSize(12);
    font.setUnderline(true);
    graphLabel->setFont(font);
    panelLayout->addWidget(graphLabel);
    panelLayout->setAlignment(Qt::AlignTop);
    panelLayout->setContentsMargins(5, 0, 0, 0);
    this->addTitle("Set the X and Y bounds", panelLayout);
    setupXSlider(panelLayout);
    setupYSlider(panelLayout);
    this->addTitle("Set the theme", panelLayout);
    setupThemeComboBox(panelLayout);
    this->addTitle("Grid options", panelLayout);
    this->setToggleGridButton(panelLayout);
    this->addTitle("Labels options", panelLayout);
    this->setLabelRadioButtons(panelLayout);
    this->addTitle("Export the graph", panelLayout);
    this->setExportButton(panelLayout);

    // Set fixed size policy for panelContainer
    panelContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    panelContainer->setFixedWidth(350);

    // Add the scatter plot to the left layout and set its size policy to expand
    surfaceLayout->addWidget(this->_surface);
    this->_surface->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    surfaceLayout->setAlignment(Qt::AlignTop); // Align the scatter plot to the top

    // Add the layouts to the main layout
    mainLayout->addLayout(surfaceLayout);
    mainLayout->addWidget(panelContainer); // Add panelContainer instead of panelLayout
    this->setLayout(mainLayout);

    // Show the widget
    this->setWindowTitle("Graph 3D");
}

Graph3DView::~Graph3DView() {
    Data::getInstance().unsubscribe(this);
    delete this->_controller;
}

/**
 * @brief Set the expression to display on the graph
 * @param expression - The expression to display
 */
void Graph3DView::setExpression(Expression *expression) const {
    this->_controller->setExpression(expression);
    this->setupAxisRanges();
}

void Graph3DView::update() {
    this->setExpression(Data::getInstance().getExpression());
}

/**
 * @brief Add a title to the panel layout
 * @param title - The title to add
 * @param panelLayout - The layout to add the title to
 */
void Graph3DView::addTitle(const QString &title, QVBoxLayout *panelLayout) {
    auto *label = new QLabel(title);
    QFont font = label->font();
    font.setUnderline(true);
    label->setFont(font);
    label->setAlignment(Qt::AlignLeft);
    label->setMargin(5);
    panelLayout->addWidget(label);
}

/**
 * @brief Setup the X slider
 * @param panelLayout - The layout to add the slider to
 */
void Graph3DView::setupXSlider(QVBoxLayout *panelLayout) {
    auto *xSlider = new QSlider(Qt::Horizontal);
    xSlider->setRange(1, 20);
    xSlider->setValue(1);
    xSlider->setTickInterval(1);
    xSlider->setTickPosition(QSlider::TicksBelow);

    // Add label to the slider
    auto *xLabel = new QLabel("X Borne");
    xLabel->setAlignment(Qt::AlignLeft);

    // Create a layout for xLabel and xValueLabel to be displayed in a row
    auto *xLabelLayout = new QHBoxLayout;
    xLabelLayout->addWidget(xLabel);

    // Add xValueLabel to display X [-value; value]
    auto *xValueLabel = new QLabel(QString("X [%1 ; %2]").arg(-xSlider->value()).arg(xSlider->value()));
    xValueLabel->setAlignment(Qt::AlignRight);
    xLabelLayout->addWidget(xValueLabel);

    // Add the xLabelLayout to the panelLayout
    panelLayout->addLayout(xLabelLayout);

    // Connect slider value changed signal to update xValueLabel
    connect(xSlider, &QSlider::valueChanged, [xValueLabel](int const value) {
        xValueLabel->setText(QString("X [%1 ; %2]").arg(-value).arg(value));
    });

    // Add the slider to the panelLayout
    panelLayout->addWidget(xSlider);

    // Connect slider value changed signal to update the controller and axis ranges
    connect(xSlider, &QSlider::valueChanged, this, [this](int const value) {
        this->_controller->setBorneX(value);
        this->setupAxisRanges();
    });
}

/**
 * @brief Setup the Y slider
 * @param panelLayout - The layout to add the slider to
 */
void Graph3DView::setupYSlider(QVBoxLayout *panelLayout) {
    auto *ySlider = new QSlider(Qt::Horizontal);
    ySlider->setRange(1, 20);
    ySlider->setValue(1);
    ySlider->setTickInterval(1);
    ySlider->setTickPosition(QSlider::TicksBelow);

    // Add label to the slider
    auto *yLabel = new QLabel("Y Borne");
    yLabel->setAlignment(Qt::AlignLeft);

    // Create a layout for yLabel and yValueLabel to be displayed in a row
    auto *yLabelLayout = new QHBoxLayout;
    yLabelLayout->addWidget(yLabel);

    // Add yValueLabel to display X [-value; value]
    auto *yValueLabel = new QLabel(QString("Y [%1 ; %2]").arg(-ySlider->value()).arg(ySlider->value()));
    yValueLabel->setAlignment(Qt::AlignRight);
    yLabelLayout->addWidget(yValueLabel);

    // Add the yLabelLayout to the panelLayout
    panelLayout->addLayout(yLabelLayout);

    // Connect slider value changed signal to update yValueLabel
    connect(ySlider, &QSlider::valueChanged, [yValueLabel](int const value) {
        yValueLabel->setText(QString("Y [%1 ; %2]").arg(-value).arg(value));
    });

    // Add the slider to the panelLayout
    panelLayout->addWidget(ySlider);

    // Connect slider value changed signal to update the controller and axis ranges
    connect(ySlider, &QSlider::valueChanged, this, [this](int const value) {
        this->_controller->setBorneY(value);
        this->setupAxisRanges();
    });
}

/**
 * @brief Setup the theme combo box to change the graph theme
 * @param panelLayout - The layout to add the combo box to
 */
void Graph3DView::setupThemeComboBox(QVBoxLayout *panelLayout) {
    // Create a combo box for theme selection
    auto *themeComboBox = new QComboBox;

    // Add theme options to the combo box
    themeComboBox->addItem("Primary", QVariant::fromValue(Q3DTheme::ThemePrimaryColors));
    themeComboBox->addItem("Digia", QVariant::fromValue(Q3DTheme::ThemeDigia));
    themeComboBox->addItem("QT", QVariant::fromValue(Q3DTheme::ThemeQt));
    themeComboBox->addItem("Stone Moss", QVariant::fromValue(Q3DTheme::ThemeStoneMoss));
    themeComboBox->addItem("Army Blue", QVariant::fromValue(Q3DTheme::ThemeArmyBlue));
    themeComboBox->addItem("Retro", QVariant::fromValue(Q3DTheme::ThemeRetro));
    themeComboBox->addItem("Ebony", QVariant::fromValue(Q3DTheme::ThemeEbony));
    themeComboBox->addItem("Isabelle", QVariant::fromValue(Q3DTheme::ThemeIsabelle));

    // Set the default theme as the current item
    themeComboBox->setCurrentIndex(0);

    // Add the combo box to the panel layout
    panelLayout->addWidget(themeComboBox);

    // Connect the currentIndexChanged signal to change the graph theme
    connect(themeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        // Retrieve the selected theme from the combo box
        auto const theme = themeComboBox->currentData().value<Q3DTheme::Theme>();

        // Apply the selected theme to the graph
        this->_surface->activeTheme()->setType(theme);
        this->_surface->activeTheme()->setGridEnabled(this->_gridEnabled);
        this->_surface->activeTheme()->setLabelsEnabled(this->_labelEnabled);
        this->_surface->activeTheme()->setLabelBorderEnabled(this->_labelBorderEnabled);
    });
}

/**
 * @brief Setup the toggle grid button
 * @param panelLayout - The layout to add the button to
 */
void Graph3DView::setToggleGridButton(QVBoxLayout *panelLayout) {
    // Create a button to toggle the grid
    auto *toggleGridButton = new QPushButton("Toggle Grid");
    toggleGridButton->setCheckable(true);
    toggleGridButton->setChecked(false);

    // Add the button to the panel layout
    panelLayout->addWidget(toggleGridButton);

    // Connect the button to toggle the grid
    connect(toggleGridButton, &QPushButton::clicked, this, [this](bool const checked) {
        this->_gridEnabled = checked;
        this->_surface->activeTheme()->setGridEnabled(checked);
    });
}

/**
 * @brief Setup the export button
 * @param panelLayout - The layout to add the button to
 */
void Graph3DView::setExportButton(QVBoxLayout *panelLayout) const {
    // Create a button to export the graph
    auto *exportButton = new QPushButton("Export Graph");

    // Add the button to the panel layout
    panelLayout->addWidget(exportButton);

    // Connect the button to export the graph
    connect(exportButton, &QPushButton::clicked, this, &Graph3DView::exportGraph);
}

/**
 * @brief Setup the radio buttons for label types
 * @param panelLayout - The layout to add the radio buttons to
 */
void Graph3DView::setLabelRadioButtons(QVBoxLayout *panelLayout) {
    // Create radio buttons for axis types
    auto *classic = new QRadioButton("Classic labels");
    auto *noLabel = new QRadioButton("No Labels");
    auto *borderedLabel = new QRadioButton("Bordered Labels");

    // Group the radio buttons so that only one can be selected at a time
    auto *axisTypeGroup = new QButtonGroup(this);
    axisTypeGroup->addButton(classic);
    axisTypeGroup->addButton(noLabel);
    axisTypeGroup->addButton(borderedLabel);

    // Set the default axis type radio button as checked
    classic->setChecked(true);

    // Add radio buttons to the panel layout
    panelLayout->addWidget(classic);
    panelLayout->addWidget(noLabel);
    panelLayout->addWidget(borderedLabel);

    // Connect radio buttons to change the axis type
    connect(classic, &QRadioButton::clicked, this, [this]() {
        // Set graduated with title axis type
        _labelBorderEnabled = false;
        _labelEnabled = true;
        this->_surface->activeTheme()->setLabelsEnabled(true);
        this->_surface->activeTheme()->setLabelBorderEnabled(false);
    });

    connect(noLabel, &QRadioButton::clicked, this, [this]() {
        _labelEnabled = false;
        _labelBorderEnabled = false;
        this->_surface->activeTheme()->setLabelsEnabled(false);
        this->_surface->activeTheme()->setLabelBorderEnabled(false);
    });

    connect(borderedLabel, &QRadioButton::clicked, this, [this]() {
        _labelEnabled = true;
        _labelBorderEnabled = true;
        this->_surface->activeTheme()->setLabelBorderEnabled(true);
        this->_surface->activeTheme()->setLabelsEnabled(true);
    });
}


/**
 * @brief Export the graph to an image
 */
void Graph3DView::exportGraph() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty()) {
        if (!this->_controller->saveImage(fileName, this->_surface)) {
            QMessageBox::critical(this, QGuiApplication::applicationDisplayName(),
                                  tr("Failed to save the image"));
        } else {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                     tr("Image saved successfully"));
        }
    }
}


/**
 * @brief Setup the axis ranges
 */
void Graph3DView::setupAxisRanges() const {
    const auto borneXFloat = static_cast<float>(this->_controller->getBorneX());
    const auto borneYFloat = static_cast<float>(this->_controller->getBorneY());
    this->_surface->axisX()->setRange(-borneXFloat - 1, borneXFloat + 1);
    this->_surface->axisY()->setRange(-borneYFloat - 1, borneYFloat + 1);
    this->_surface->axisZ()->setRange(this->_controller->getMin() - 1, this->_controller->getMax() + 1);
}
