#include "graphics.h"       
#include "City.h"
#include "mainwindow.h"

#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTextFormat>
#include <QDebug>

#include <cmath>
#include <regex>

/* * Construct a GameWidget Object
 * 
 * Calls constructor for a GameWidge object.
 * 
 * @param parent A reference to the parent QWidget.
 * */
GameWidget::GameWidget(QWidget* parent) :
    QWidget(parent),
    city(dynamic_cast<MainWindow *>(parent)->city),
    grid_size(city->get_grid_size()),
    scroll_x(0), scroll_y(0),
    scale(1.0f),
    UP(false), DOWN(false), LEFT(false), RIGHT(false),  
    god_mode(false),       // For demo Purpose. In default, god mode should not be activated
    tick(0),
    hovering_grid_x(-1), hovering_grid_y(-1)
{
    load_icons();
    setMouseTracking(true);
    grabKeyboard();
}

/** Destruct a GameWidget Object
*
* Calls destructor for a Gamewidge object.
*
**/
GameWidget::~GameWidget() {
    dealloc_icons();
}

/** Determine the change of view area 
*
* Change the areas viewed in the window according to which key user's pressed 
* (According to boolean values UP RIGHT DOWN LEFT)
*
**/
void GameWidget::loop() {
    scroll_x += (int) (15.0f * ((int) RIGHT - (int) LEFT) / scale);
    scroll_y += (int) (15.0f * ((int) DOWN - (int) UP) / scale);
    repaint(0, 0, width(), height());
    ++tick;
}

/** Response to the key pressed
*
* Change the boolean value (UP, DOWN, LEFT, RIGHT, god_mode) according 
* to the key user's pressed
*
* @param event  A point to a QKeyEvent which records user's input
*
**/
void GameWidget::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_W:
        UP = true;
        break;
    case Qt::Key::Key_S:
        DOWN = true;
        break;
    case Qt::Key::Key_A:
        LEFT = true;
        break;
    case Qt::Key::Key_D:
        RIGHT = true;
        break;
    // When Key 'B' is pressed, god mode activates and set budget to 99999.
    case Qt::Key::Key_B:
        god_mode = true;
        city->set_budget(99999);
        break;
    }
}


/** Response to the key released (not pressed)
*
* Change the boolean value (UP, DOWN, LEFT, RIGHT, god_mode) according 
* to the key user's released
*
* @param event  A point to a QKeyEvent which records user's input
*
**/
void GameWidget::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key::Key_W:
        UP = false;
        break;
    case Qt::Key::Key_S:
        DOWN = false;
        break;
    case Qt::Key::Key_A:
        LEFT = false;
        break;
    case Qt::Key::Key_D:
        RIGHT = false;
        break;
    // When key 'B' is realized, god mode deactivated
    case Qt::Key::Key_B:
        god_mode = false;
        break;
    }
}

/** Response to user's input from scrolling wheel
*
* modifying the data member scale. 
* Meanwhile, 0.1f < scale < 10.0f
*
* @param event  A pointer to QWheelEvent
*
**/
void GameWidget::wheelEvent(QWheelEvent* event) {
    scale = (float) (scale * exp(event->angleDelta().y() / 720.0));
    if (scale > 10.0f) {
        scale = 10.0f;
    }
    if (scale < 0.1f) {
        scale = 0.1f;
    }
}

/** Response to user's input from releasing one's mouse click
*
* If users click on grid cell with a node, then show the information of the node in a message box
* (Left click: Short info; Right Click: Long info)
* If users selected buildings button and click on an empty grid cell, then build new building / Road
* If users selected delete button and click on a grid cell with a node, then demolish the building
*
* @param event  A pointer to QWheelEvent
*
**/
void GameWidget::mouseReleaseEvent(QMouseEvent* event) {
    int screen_x = event->x();
    int screen_y = event->y();
    int x, y;
    obtain_grid_coordinates(screen_x, screen_y, x, y);

    // Check if selected point lies on the grid
    if (x >= 0 && y >= 0 && x < grid_size && y < grid_size) {
        MainWindow *main_window = dynamic_cast<MainWindow *>(window());
        MainWindow::SideMenuButton button_selected = main_window->get_selected_side_menu_button();
        if (button_selected != MainWindow::SideMenuButton::NAVIGATE) {
            if (event->button() == Qt::MouseButton::RightButton) {
                main_window->on_side_menu_button_clicked(MainWindow::SideMenuButton::NAVIGATE);
            } else if (event->button() == Qt::MouseButton::LeftButton) {
                // If the selected button are buildings
                if (button_selected != MainWindow::SideMenuButton::DEMOLISH && city->is_empty_at(x, y)) {
                    city->construct_at(static_cast<Node::Type>(button_selected), x, y);

                    // Trick to jump back to navigation if player does not have enough budget for the building
                    main_window->on_side_menu_button_clicked(button_selected);
                }

                // Selected button is delete
                else if (button_selected == MainWindow::SideMenuButton::DEMOLISH && !city->is_empty_at(x, y)) {
                    city->demolish_at(x, y);
                }
            }
        } else if (!city->is_empty_at(x, y)) {
            QMessageBox *mb = new QMessageBox{window()};
            mb->setWindowTitle("Simple City");
            mb->setStyleSheet("font: 14pt \"Comic Sans MS\";");

            if (event->button() == Qt::MouseButton::LeftButton) {
                mb->setText(QString::fromStdString(
                        "<p style='text-align: center;'>" +
                        std::regex_replace(city->get_at(x, y)->get_short_information(), std::regex{"\n"}, "<br>") +
                        "</p>"
                ));
            } else if (event->button() == Qt::MouseButton::RightButton) {
                mb->setText(QString::fromStdString(
                        "<p style='text-align: center;'>" +
                        std::regex_replace(city->get_at(x, y)->get_long_information(), std::regex{"\n"}, "<br>") +
                        "</p>"
                ));
            }
            mb->setAttribute(Qt::WA_DeleteOnClose, true);
            mb->show();
        }
    }
}

/** Response to user's mouse move event
*
* Modify the button group / side menu status using event's coordinates
*
* @param event  A pointer to QMouseEvent
*
**/
void GameWidget::mouseMoveEvent(QMouseEvent* event) {
    int screen_x = event->x();
    int screen_y = event->y();

    MainWindow *main_window = dynamic_cast<MainWindow *>(window());
    MainWindow::SideMenuStatus button_group_status = main_window->get_side_menu_status();
    if (screen_x > width() - 100) {
        if (button_group_status == MainWindow::SideMenuStatus::HIDDEN) {
            main_window->set_side_menu_status(MainWindow::SideMenuStatus::HIDDEN_TO_VISIBLE);
        }
    } else if (screen_x < width() - 420){
        if (button_group_status == MainWindow::SideMenuStatus::VISIBLE) {
            main_window->set_side_menu_status(MainWindow::SideMenuStatus::VISIBLE_TO_HIDDEN);
        }
    }

    if (screen_x > width() - 420 || button_group_status == MainWindow::SideMenuStatus::HIDDEN){ // Does handle only if the cursor is on the to-be menu
        int x, y;

        obtain_grid_coordinates(screen_x, screen_y, x, y);

        hovering_grid_x = x;
        hovering_grid_y = y;
    }
}


/** Obtain (/convert) the grid coordinates from actual coordinates of window
*
* grid coordinate x is given by : (rx + grid_size * 50) / 100
* grid coordinate y is given by : (ry + grid_size * 50) / 100
*
* @param rx  An int of real coordinate x
* @param ry  An int of real coordinate y
* @param x   A x coordinate for return
* @param y   A y coordinate for return
*
**/
void GameWidget::obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y) {
    x = (rx + grid_size * 50) / 100;
    y = (ry + grid_size * 50) / 100;
}

/** Obtain (/convert) the grid coordinates
*
* compute grid coordinates using to_real_coordinates() and obtain_grid_coordinates_from_real()
*
* @param dispx  An int of display coordinate x
* @param dispy  An int of display coordinate y
* @param x   A x coordinate for return
* @param y   A y coordinate for return
*
**/
void GameWidget::obtain_grid_coordinates(int dispx, int dispy, int& x, int& y) {
    int rx, ry;
    to_real_coordinates(dispx, dispy, rx, ry);
    obtain_grid_coordinates_from_real(rx, ry, x, y);
}

/** convert coordinates to Display coordinates
*
* Display coordinate by setting dispx = (int)((fx - scroll_x) * scale) + width() / 2
* and dispy = (int)((fy - scroll_y) * scale) + height() / 2
*
* @param x       An integer of coordinate x
* @param y       An integer of coordinate y
* @param dispx   A display x coordinate for return
* @param dispy   A display y coordinate for return
*
**/
void GameWidget::to_display_coordinates(int x, int y, int& dispx, int& dispy) {
    float fx = x, fy = y;
    dispx = (int)((fx - scroll_x) * scale) + width() / 2;
    dispy = (int)((fy - scroll_y) * scale) + height() / 2;
}

/** convert Display coordinates to real coordinates
*
* Compute real coordinates by : fx = dispx - width() / 2
*                               fy = dispy - height() / 2
*
* @param dispx  An int of display coordinate x
* @param dispy  An int of display coordinate y
* @param x   A x coordinate for return
* @param y   A y coordinate for return
*
**/
void GameWidget::to_real_coordinates(int dispx, int dispy, int& x, int& y) {
    float fx = dispx - width() / 2, fy = dispy - height() / 2;

    x = (int)(fx / scale + scroll_x);
    y = (int)(fy / scale + scroll_y);
}

/** Draw Line from (x1,y1) to (x2,y2)
*
* Convert x1,x2,y1,y2 into display coordinates, and draw lines between (dispx1, dispy1) and (dispx2, dispy2)
*
* @param Paint  Reference to a QPainter object
* @param x1  An int of actual coordinate x1
* @param y1  An int of actual coordinate y1
* @param x2  An int of actual coordinate x2
* @param y2  An int of actual coordinate y2
*
**/
void GameWidget::drawLine(QPainter& paint, int x1, int y1, int x2, int y2) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x1, y1, dispx1, dispy1);
    to_display_coordinates(x2, y2, dispx2, dispy2);

    paint.drawLine(dispx1, dispy1, dispx2, dispy2);
}

/** FillRect on the window 
*
* Convert coordinates to display coordinates, and paint with reference of width and height.
*
* @param paint Reference to a QPainter object
* @param x     An int of actual x coordinate
* @param y     An int of actual y coordinate
* @param w     An int of width
* @param h     An int of height
* @param brush A constant reference of QBrush 
*
**/
void GameWidget::fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush& brush) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.fillRect(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, brush);
}

/** Draw Pixmap on the window 
*
* Convert coordinates to display coordinates, and paint with reference of width and height.
*
* @param paint Reference to a QPainter object
* @param x     An int of actual x coordinate
* @param y     An int of actual y coordinate
* @param w     An int of width
* @param h     An int of height
* @param pixmap A constant reference of QPixmap 
*
**/
void GameWidget::drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap& pixmap) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.drawPixmap(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, pixmap);
}

/** A Helper Function 
*
* A helper function that determine whether the node contains type.
* If any node is a nullptr (no building at that node), return -2
* If one node is residential object and the other one is gold mine, return 0
* If one node is residential object and the other one is not a gold mine, return 1
* If both node is Health object, return -1
* Otherwise, return -2
*
* @param b1 A pointer to a node object
* @param b2 A pointer to a node object
*
* @return an int (either -2/-1/0/1)
*
**/
int contains_type(Node* b1, Node* b2) {
    if (b1 == nullptr || b2 == nullptr) {
        return -2;
    }

    Node::Category t1 = b1->get_category();
    Node::Category t2 = b2->get_category();

    if (t1 == Node::Category::RESIDENTIAL) {
        return (b2->get_type() == Node::Type::GOLD_MINE) ? 0 : 1;
    }
    if (t2 == Node::Category::RESIDENTIAL) {
        return (b1->get_type() == Node::Type::GOLD_MINE) ? 0 : 1;
    }
    if (t1 == t2 && t2 == Node::Category::HEALTH) {
        return -1;
    }

    return -2;
}

/** A Helper Function to determine test Color
*
* If dcolor is -1, change color to red
* If dcolor is 0 , change color to white
* If dcolor is 1 , change color to green
*
* @param paint A reference to a QPainter 
* @param dcolor An int representing a color
*
**/
void tsetColor(QPainter& paint, int dcolor) {
    QPen p = paint.pen();
    p.setWidth(7);
    switch (dcolor) {
    case -1:
        // RED
        p.setColor(QColor::fromRgb(255, 0, 0));
        break;
    case 0:
        //WHITE
        p.setColor(QColor::fromRgb(255, 255, 255));
        break;
    case 1:
        // GREEN
        p.setColor(QColor::fromRgb(0, 255, 0));
        break;
    }
    paint.setPen(p);
}

/** A Helper Function to Determine the color of pen according to the traffic flow amount 
*
* If traffic < 100, change color to dark green
* If 100 < traffic < 200, change color to yellow
* If traffic > 200, change color to dark red
*
* @param paint A reference to a QPainter 
* @param traffic An int indicating the traffic flow
*
**/
void RoadColor(QPainter& paint, int traffic) {
    QPen p = paint.pen();
    p.setWidth(7);
    if (traffic < 100){
        // if traffic flow is smaller than 100 , Change to Dark green
        p.setColor(QColor::fromRgb(0, 102, 51));
    }else if (traffic < 200){
        // if traffic flow is between 100 and 200 , Change to Yellow
        p.setColor(QColor::fromRgb(255, 255, 0));
    }else{
        // if traffic flow is larger than 200 , Change to Red
        p.setColor(QColor::fromRgb(255, 0, 0));
    }
    paint.setPen(p);
}

/** Paint Event : Determine the paint event according to the mode 
*
* Draw Roads on grid, then paint according to overlay function
* if normal overlay is selected, no action needed
* if road overlay is selected, paint line indicating the traffic flow
* if type overlay is selected, paint the whole grid which indicated the category of node
* If neighbor overlay is selected, paint line linking node with neighboring effect
* The, draw the buildings, the grid line, and player statistics
*
* @param event A reference to a QPainterEvent
*
**/
void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter paint{ this };

    // Set green background
    paint.fillRect(0, 0, width(), height(), QBrush{ QColor::fromRgb(100,200,100) });

    QFont ft;
    ft.setPixelSize(25);
    ft.setBold(true);
    ft.setFamily("Comic Sans MS");
    paint.setFont(ft);

    const int min = -grid_size * 50;
    const int max = grid_size * 50;// Draw special overlays on the grid

    // Draw Roads on the grid
    // Road cell icon is handled first so to allow road overlay paint can cover the road
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (!city->is_empty_at(x, y)) {
                Node::Type type = city->get_at(x, y)->get_type();
                if (type == Node::Type::STREET || type == Node::Type::AVENUE){
                    drawPixmap(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100,
                               get_road_icon(type, x, y));
                }
            }
        }
    }
    switch (dynamic_cast<MainWindow *>(window())->get_selected_overlay_button()) {
        case MainWindow::OverlayButton::NORMAL:
            // In normal mode, no overlay actions required
            break;
        case MainWindow::OverlayButton::ROAD:{
         // Changing the grid cell color into dark green / yellow / red according to the traffic flow 
         // Note : Only Avenue / Street will change the color.                                        
            QPen original = paint.pen();
            // Go into every suitable grid cell, which is :
            for (int x = 0; x < grid_size; x++) {
                for (int y = 0; y < grid_size; y++) {
                    if (!city->is_empty_at(x, y)){                                       // Not an empty cell and,
                        if (city->get_at(x, y)->get_category() == Node::Category::ROAD){ // is in road type
                            int traffic_flow_num = 0;
                            // cast the pointer from Pointer to Node into Pointer to Avenue / Street
                            // In order to access get_traffic_flow()
                            if (city->get_at(x, y)->get_type() == Node::Type::AVENUE){
                                traffic_flow_num = static_cast<Avenue*>(city->get_at(x,y))->get_traffic_flow();
                            }
                            if (city->get_at(x, y)->get_type() == Node::Type::STREET){
                                traffic_flow_num = static_cast<Street*>(city->get_at(x,y))->get_traffic_flow();
                            }
                            RoadColor(paint,traffic_flow_num);
                            // Go through neighboring cell :
                            // Direction  : S->W->N->E
                            // value of i : 0  1  2  3
                            for (int i = 0; i < 4; i++){
                                // Check Whether neighboring cell have road type object
                                if (!city->get_at(x, y)->is_neighbor_empty(static_cast<Node::Direction>(i))){
                                    switch(i){
                                        case 0: // Linked with Bottom
                                            drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                            (x - grid_size / 2) * 100 + 50, (y + 0.5 - grid_size / 2) * 100 + 50);
                                            break;
                                        case 1: // Linked with Left
                                            drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                             (x + 0.5 - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50);
                                             break;
                                        case 2: // Linked with top
                                            drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                            (x - grid_size / 2) * 100 + 50, (y - 0.5 - grid_size / 2) * 100 + 50);
                                            break;
                                        case 3: // Linked with Right
                                            drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                             (x - 0.5 - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50);
                                            break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            paint.setPen(original);
            break;
        }
        case MainWindow::OverlayButton::TYPE: {
            for (int x = 0; x < grid_size; x++) {
                for (int y = 0; y < grid_size; y++) {
                    if (!city->is_empty_at(x, y)) {
                        // if the cell is road, no action is needed, since the icon will cover the whole grid
                        if (city->get_at(x, y)->get_category() == Node::Category::ROAD){continue;}
                        QBrush brush;
                        switch (city->get_at(x, y)->get_category()) {
                            case Node::Category::ROAD:
                                // No need to set color since the street / avenue occupied whole cell area.
                                break;
                            case Node::Category::RESIDENTIAL:
                                brush.setColor(QColor::fromRgbF(0, 0, 1, 0.8f));
                                break;
                            case Node::Category::REVENUE:
                                brush.setColor(QColor::fromRgbF(1, 1, 0, 0.8f));
                                break;
                            case Node::Category::HEALTH:
                                brush.setColor(QColor::fromRgbF(1, 0, 0, 0.8f));
                                break;
                        }
                        brush.setStyle(Qt::SolidPattern);
                        fillRect(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100, brush);
                    }
                }
            }
            break;
        }
        case MainWindow::OverlayButton::NEIGHBOR: {
            QPen original = paint.pen();
            for (int x = 0; x < grid_size; x++) {
                for (int y = 0; y < grid_size; y++) {
                    // With bottom
                    int dcolor = contains_type(city->get_at(x, y), city->get_at(x, y + 1));
                    if (dcolor != -2) {
                        tsetColor(paint, dcolor);
                        drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                 (x - grid_size / 2) * 100 + 50, (y + 1 - grid_size / 2) * 100 + 50);
                    }

                    // With left
                    dcolor = contains_type(city->get_at(x, y), city->get_at(x + 1, y));
                    if (dcolor != -2) {
                        tsetColor(paint, dcolor);
                        drawLine(paint, (x - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50,
                                 (x + 1 - grid_size / 2) * 100 + 50, (y - grid_size / 2) * 100 + 50);
                    }
                }
            }
            paint.setPen(original);
            break;
        }
    }

    // Draw buildings on the grid
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (!city->is_empty_at(x, y)) {
                Node::Type type = city->get_at(x, y)->get_type();
                if (!(type == Node::Type::STREET || type == Node::Type::AVENUE)){
                    drawPixmap(paint, (x - grid_size / 2) * 100, (y - grid_size / 2) * 100, 100, 100,
                               ICONS[static_cast<int>(type) - 1]);
                }
            }
        }
    }
    // Render extra effects on the grid, depending on the build mode
    if (hovering_grid_x >= 0 && hovering_grid_y >= 0 && hovering_grid_x < grid_size && hovering_grid_y < grid_size)
        if ((tick / 10) % 2 == 0) {
            MainWindow::SideMenuButton button_selected = dynamic_cast<MainWindow *>(window())->get_selected_side_menu_button();
            if (button_selected != MainWindow::SideMenuButton::DEMOLISH &&
                button_selected != MainWindow::SideMenuButton::NAVIGATE &&
                city->is_empty_at(hovering_grid_x, hovering_grid_y)) {

                QPixmap icon;
                if (button_selected == MainWindow::SideMenuButton::AVENUE)
                    icon = get_road_icon(Node::Type::AVENUE, hovering_grid_x, hovering_grid_y);
                else if (button_selected == MainWindow::SideMenuButton::STREET)
                    icon = get_road_icon(Node::Type::STREET, hovering_grid_x, hovering_grid_y);
                else
                    icon = ICONS[static_cast<int>(button_selected) - 1];

                drawPixmap(paint, (hovering_grid_x - grid_size / 2) * 100, (hovering_grid_y - grid_size / 2) * 100, 100,
                           100, icon);

            } else if (button_selected == MainWindow::SideMenuButton::DEMOLISH &&
                       !city->is_empty_at(hovering_grid_x, hovering_grid_y)) {
                fillRect(paint, (hovering_grid_x - grid_size / 2) * 100, (hovering_grid_y - grid_size / 2) * 100, 100,
                         100, QBrush{QColor::fromRgbF(1.0f, 0, 0, 0.5f)});
            }
        }

    // Draw grid lines
    for (int x = 0; x <= grid_size; x++) {
        int xpos = (x - grid_size / 2) * 100;
        drawLine(paint, xpos, min, xpos, max);
    }
    for (int y = 0; y <= grid_size; y++) {
        int ypos = (y - grid_size / 2) * 100;
        drawLine(paint, min, ypos, max, ypos);
    }

    // Draw player statistics
#define STAT_WIDTH 500
#define HEIGHT 40
    paint.drawText(10, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
                   "Turn " + QString::number(city->get_turn()) + ": $" + QString::number(city->get_budget()));
    paint.drawText(10, 60 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "Revenue: " + QString::number(city->get_revenue()));
    paint.drawText(10, 110 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
                   "Max Population: " + QString::number(city->get_max_population()));
    paint.drawText(10, 160 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
                   "Population: " + QString::number(city->get_population()));
    paint.drawText(10, 210 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
                   "Population Change: " + QString::number(city->get_population_growth()));
    paint.drawText(10, 260 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop,
                   "Population Growth Rate: " + QString::number(city->get_population_growth_rate()));
}

/** Load the icons 
*
* Set the dynamic QPixmap array ICONS into correct graphics files
*
**/
void GameWidget::load_icons() {
    ICONS = new QPixmap[6]{ {":/resources/images/clinic.png"},
                            {":/resources/images/hospital.png"},
                            {":/resources/images/silver_mine.png"},
                            {":/resources/images/gold_mine.png"},
                            {":/resources/images/house.png"},
                            {":/resources/images/apartment.png"} };
    STREET_ICONS = new QPixmap[16];
    AVENUE_ICONS = new QPixmap[16];
    for(int i = 0; i < 16; i++){
        STREET_ICONS[i] = QPixmap {":/resources/images/street_" + QString::number(i) + ".png"};
        AVENUE_ICONS[i] = QPixmap {":/resources/images/avenue_" + QString::number(i) + ".png"};
    }
}

/** Deallocating memory of icons
*
* Deallocating memory of icons, which are dynamically allocated 
*
**/
void GameWidget::dealloc_icons() {
    delete[] ICONS;
    delete[] STREET_ICONS;
    delete[] AVENUE_ICONS;
}

/** Get Variety of Road Icon based on it's (x,y) coordinate
*
* Identify presence of roads node in the neighboring grids, 
* and show the respective road icon for that grid cell
*
* @param type enum Node::Type, indicate the type of grid cell
* @param x An integer storing the x coordinate
* @param y An integer storing the y coordinate
*
* @return QPixmap The directory of the graphics
**/
QPixmap GameWidget::get_road_icon(Node::Type type, int x, int y){

    bool is_empty[4] = {false};

    // Saves if the node is empty for N, E, S, W directions
    for (int i = 0; i < 4; i++) {
        if (city->get_at(x, y) != nullptr)
            is_empty[i] = city->get_at(x, y)->is_neighbor_empty(static_cast<Node::Direction>(i));
        else
            is_empty[i] = true;
    }

    /*  Return road icon according to type and neighbors
        Tileset filenames are encoded such that the number after its suffix would be:
        !is_empty[north] + 2 * !is_empty[east] + 4 * !is_empty[south] + 8 * !is_empty[west] */
    if (type == Node::Type::STREET) {
        return STREET_ICONS[ !is_empty[2] + 2 * !is_empty[1] + 4 * !is_empty[0] + 8 * !is_empty[3] ];
    } else if (type == Node::Type::AVENUE) {
        return AVENUE_ICONS[ !is_empty[2] + 2 * !is_empty[1] + 4 * !is_empty[0] + 8 * !is_empty[3] ];
    } else return QPixmap {":/resources/images/avenue_15.png"};

}
