#include "SkyplotWidget.h"
#include <QGuiApplication>
#include <QtGui>
#include <stdlib.h>
#include <QDebug>
#include <QtMath>
#include <QString>

SkyplotWidget::SkyplotWidget(QWidget *parent)
    : QWidget(parent)
    , flash( false )
    , p_marginScale( 0.78 )
    , p_satScale( 0.03 )
    , p_fontScale( 0.02 )
    , p_gridColor( QColor( 150, 150, 150, 255 ) )
    , p_gridTextColor( QColor( 210, 210,210))
    , p_gridWidth( 3 )
    , p_ellipses( 3 )
    , p_crosses( 3 )
    , p_textMargin( 10 )
    , p_flashIntervall( 500 )
    , p_withGridLabels( true )
    , p_antialiased( true )
    , m_pieRotate(0)
{
    flashTimer.setInterval( p_flashIntervall );
    connect( &flashTimer, SIGNAL( timeout() ), this, SLOT( change_flash() ) );
    flashTimer.start( p_flashIntervall );
    connect(&m_PieSpeed,SIGNAL(timeout()),this,SLOT(pie_speed()));
    m_PieSpeed.start(50);
}

void SkyplotWidget::change_flash( void )
{
    flash = !flash;
    this->update();
}
void SkyplotWidget::pie_speed( void )
{
    m_pieRotate -= 10;
    this->update();
}

void SkyplotWidget::paintEvent(QPaintEvent *)
{
    QSize          widgetSize(this->size());
    QPalette       p = palette();
    QPainter      *painter = new QPainter(this);
    float          topMargin ;
    float          leftMargin;
    float          size;
    float          satelliteSize;
    float          fontSize;
    float          availableWidth    = widgetSize.width ();
    float          availableHeight   = widgetSize.height();

    if( availableHeight > availableWidth )
    {
        size = widgetSize.width() * p_marginScale;
        topMargin   = ( widgetSize.width() - widgetSize.width() * p_marginScale + widgetSize.height() - widgetSize.width() ) / 2.0;
        leftMargin  = ( widgetSize.width() - widgetSize.width() * p_marginScale ) / 2.0;
    }
    else
    {
        size = widgetSize.height() * p_marginScale;
        leftMargin = ( widgetSize.height() - widgetSize.height() * p_marginScale + widgetSize.width() - widgetSize.height()) / 2.0;
        topMargin  = ( widgetSize.height() - widgetSize.height() * p_marginScale ) / 2.0;
    }

    satelliteSize = size * p_satScale;
    painter->setRenderHint(QPainter::Antialiasing, p_antialiased);
    painter->translate( leftMargin, topMargin );  //重新设置坐标原点
    fontSize = size * p_fontScale;
    painter->setFont(QFont( "Arial", static_cast< int >(fontSize)));

    //圆圈
    for(int i=0; i <= p_ellipses; i++)
    {
        float radius = size / 2.0 - i * ( size / ( 2.0  * p_ellipses ));
        painter->setPen( QPen( p_gridColor, p_gridWidth ) );
        painter->drawEllipse(QPoint( size/2.0, size/2.0 ), static_cast< int >( radius ), static_cast< int >(radius));
        if(p_withGridLabels)
        {
            painter->setPen( QPen( p_gridTextColor, p_gridWidth -2.5 ) );
            double tmp = ((p_ellipses - i) * (mMonitorScope / p_ellipses));
            QString distance = QString::number(((p_ellipses - i) * (mMonitorScope / p_ellipses)) ,10 , 2);
            painter->drawText(QPoint(size/2.0 + p_textMargin, size/2.0 - (radius + p_textMargin)), QString("%1 km").arg(distance)); //距离刻度
        }
    }

    //十字架
    for(int i=0; i < p_crosses; i++)
    {
        QLineF line1,line2;
        float angle = (static_cast<float>(i) * 90.0) / (static_cast<float>(p_crosses));
        line1.setP1( QPoint( size/2.0, size/2.0 ) );
        line1.setLength( size/2.0 );

        QRectF textRect(0, 0, 4.0 * fontSize, fontSize + 2.0);

        for(int c = 0; c < 4; c++)
        {
            line1.setAngle(angle + c*90.0 + 90.0);
            painter->setPen(QPen(p_gridColor, p_gridWidth));
            painter->drawLine(line1);
            if( p_withGridLabels )
            {
                painter->setPen(QPen( p_gridTextColor, p_gridWidth));
                line2 = QLineF(line1);
                line2.setLength(size/2.0 + 2.0 * fontSize);
                textRect.moveCenter(line2.p2());
                if(i > 0)
                    painter->drawText( textRect, Qt::AlignCenter, QString("%1").arg((int)(360 - (c*90 ) - angle) , 3 , 10 , QChar('0')));
                else
                {
                    if(c == 0)
                    {
                        painter->drawText( textRect, Qt::AlignCenter,QString("000"));
                    }
                    else if(c == 1)
                    {
                        painter->drawText( textRect, Qt::AlignCenter, QString("270"));
                    }
                    else if(c == 2)
                    {
                        painter->drawText( textRect, Qt::AlignCenter, QString("180"));
                    }
                    else if(c == 3)
                    {
                        painter->drawText( textRect, Qt::AlignCenter, QString("090"));
                    }
                }
            }
        }
    }

    QBrush innerBrush = QBrush( Qt::SolidPattern );
    QBrush outerBrush = QBrush( );
    //卫星
    foreach( auto s, satellites )
    {
        //------w---设置每一个卫星的大小
        satelliteSize = size * s.rsize;
        // skip invisible satellites
        if(     s.state & SatelliteState::Invisible       ||  // the invisible flag is set

                ( !( s.state & SatelliteState::Visible ) &         // neither visible nor half-visible
                  !( s.state & SatelliteState::HalfVisible ) ) ||

                (  s.state & SatelliteState::Flashing && flash )    // flashing flag is set and flash is active
                )
            continue;

        QRectF labelRect( 0, 0, s.label.length() * satelliteSize, satelliteSize+2 );

        double nmdX = 0,nmdY = 0;  //卫星的X轴坐标,卫星的Y轴坐标
        calculatePos(s.az , s.distance ,nmdX, nmdY);
        QPoint satPos(size/2.0 + size*(nmdX/mMonitorScope) * 0.5,size/2.0 +  size*(nmdY/mMonitorScope) * 0.5);

        // define the color's alpha value (0.3 or 1.0)
        QColor innerColor = s.innerColor;
        QColor outerColor = s.outerColor;
        QColor fontColor  = s.fontColor;
        if( s.state & SatelliteState::Visible )
        {
            innerColor.setAlphaF( 1.0 );
            outerColor.setAlphaF( 1.0 );
            fontColor.setAlphaF( 1.0 );
        }
        else
        {
            innerColor.setAlphaF( 0.3 );
            outerColor.setAlphaF( 0.3 );
            fontColor.setAlphaF( 0.3 );
        }

        // paint the inner circle
        innerBrush.setColor( innerColor );
        painter->setBrush( innerBrush );
        if( s.state & SatelliteState::Marked )
            painter->setPen( QPen( outerColor, satelliteSize/4 ) );
        else
            painter->setPen( QPen( p_gridColor, 0 ) );
        painter->drawEllipse( satPos, static_cast< int >( satelliteSize ), static_cast< int >( satelliteSize ) );


        // write the text
        painter->setPen( QPen( fontColor, 2 ) );
        painter->setFont( QFont( "Arial", static_cast< int >( satelliteSize ),  QFont::Bold ) );
        labelRect.moveCenter( satPos );
        painter->drawText( labelRect, Qt::AlignCenter, s.label );

    }

    foreach (auto l, indicatrix)
    {
        if(  l.lineState & SatelliteState::Invisible       ||  // the invisible flag is set
             ( !( l.lineState & SatelliteState::Visible ) &         // neither visible nor half-visible
               !( l.lineState & SatelliteState::HalfVisible ) ) ||
             (  l.lineState & SatelliteState::Flashing && flash )    // flashing flag is set and flash is active
             )
            continue;

        QPoint spoint ( l.point1.rx() * size / 100 + size/2, l.point1.ry() * size/100 + size/2);
        QPoint epoint ( l.point2.rx() * size / 100 + size/2, l.point2.ry() * size/100 + size/2);

        painter->setPen(QPen(l.lineColor,1.5,Qt::DashDotLine,Qt::RoundCap));
        painter->drawLine(spoint,epoint);
    }

    //余晖扫描
    //   int len = m_drawArea.width();
    qreal x = size/2.0 + (qreal)size/2 * cos(-m_pieRotate*3.14159/180);
    qreal y = size/2.0 + (qreal)size/2 * sin(-m_pieRotate*3.14159/180);
    painter->setPen(QPen(Qt::green));
    painter->drawLine(QPoint( size/2.0, size/2.0 ),QPointF(x,y));

    //扇形
    QConicalGradient gradient;
    gradient.setCenter(QPoint( size/2.0, size/2.0 ));
    gradient.setAngle(m_pieRotate + 180); //渐变与旋转方向恰好相反，以扇形相反的边作为渐变角度。
    gradient.setColorAt(0.4,QColor(169,253,51,100)); //从渐变角度开始0.5 - 0.75为扇形区域，由于Int类型计算不精确，将范围扩大到0.4-0.8
    gradient.setColorAt(0.8,QColor(169,253,51,0));
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawPie(0,0,size,size,m_pieRotate*16,90*16);
    //--------------------------------------------------
    delete painter;
}

bool SkyplotWidget::calculatePos(const double &az, const double &distance, double &x, double &y)
{
    if((az>= 0) && (az <= 360))
    {

        if(equal(az , 0) && equal(az ,180))  //目标在Y轴上
        {
            if(equal(az , 0))
            {
                x = 0.0;
                y = -distance;
            }
            else if(equal(az , 180))
            {
                x = 0.0;
                y = distance;
            }
        }
        if(equal(az , 90) && equal(az ,270)) //目标在X轴上
        {
            if(equal(az , 90))
            {
                x = distance;
                y = 0.0;
            }
            else if(equal(az , 270))
            {
                x = -distance;
                y = 0.0;
            }
        }

        if((az >=0) && (az<=90))             //第一象限
        {
            double radian = az * M_PI/180;             //将角度转弧度
            x = qSin(radian) * distance;         //三角函数公式 , 弧度转角度
            y = -(qCos(radian) * distance);
        }
        else if((az >90) && (az<=180))       //第四象限
        {
            double radian = (180 - az)* M_PI/180;
            x = qSin(radian) * distance;
            y = qCos(radian) * distance;
        }
        else if((az >180) && (az<=270))      //第三象限
        {
            double radian = (270- az)* M_PI/180;
            y = qSin(radian) * distance;    //对边是y
            x = -(qCos(radian) * distance); //邻变是x
        }
        else if((az >270) && (az<=360))      //第二象限
        {
            double radian =(360 - az)* M_PI/180;
            x = -(qSin(radian) * distance);
            y = -(qCos(radian) * distance);
        }
        return true;
    }
    else
        return false;
}

bool SkyplotWidget::equal(double num1, double num2)
{
    if((num1-num2>-0.000001)&&(num1-num2)<0.000001)
        return true;
    else
        return false;
}

void SkyplotWidget::setMonitorScope(double d)
{
    mMonitorScope = d;
}

//目标ID
//方位角
//仰角
//大小
void SkyplotWidget::insert(  int id, float az, float distance, float si, const QString & label, const QColor & outerColor, const QColor & innerColor, const QColor & fontColor, SatelliteState  state )
{
    Satellite   sat;
    sat.label      = label;
    sat.az         = az;
    sat.distance   = distance;
    sat.rsize      = si;
    sat.state      = state;
    sat.innerColor = innerColor;
    sat.outerColor = outerColor;
    sat.fontColor  = fontColor;

    this->update();

    satellites.insert( id, sat );
}

//----------------- W --- start ------------
void SkyplotWidget::insertLine(int id, const QPoint p1, const QPoint p2, const QColor &lineColor, SatelliteState state )
{
    Myline  line;
    line.point1     = p1;
    line.point2     = p2;
    line.lineColor  = lineColor;
    line.lineState  = state;

    indicatrix.insert(id,line);
}

void SkyplotWidget::setLineColor( int id, const QColor & c )
{
    indicatrix[ id ].lineColor = c;
    this->update();
}

void SkyplotWidget::setLineState( int id, SatelliteState state )
{
    indicatrix[ id ].lineState = state;
    this->update();
}
void SkyplotWidget::setLinePoint(int id, const QPoint p1, const QPoint p2)
{
    indicatrix[ id ].point1 = p1;
    indicatrix[ id ].point2 = p2;
    this->update();
}
void SkyplotWidget::setLinePoint2(int id,  const QPoint p2)
{
    indicatrix[ id ].point2 = p2;
    this->update();
}
//-------------------------- end ----------------

void SkyplotWidget::remove( int id )
{
    satellites.remove( id );
}

bool SkyplotWidget::contains( int id ) const
{
    return satellites.contains( id );
}

QColor SkyplotWidget::innerColor( int id ) const
{
    return satellites[ id ].innerColor;
}

QColor SkyplotWidget::outerColor( int id ) const
{
    return satellites[ id ].outerColor;
}

QColor SkyplotWidget::fontColor( int id ) const
{
    return satellites[ id ].fontColor;
}

void SkyplotWidget::setInnerColor( int id, const QColor & c )
{
    satellites[ id ].innerColor = c;
    this->update();
}

void SkyplotWidget::setOuterColor( int id, const QColor & c )
{
    satellites[ id ].outerColor = c;
}

void SkyplotWidget::setFontColor( int id, const QColor & c )
{
    satellites[ id ].fontColor = c;
}

SkyplotWidget::SatelliteState  SkyplotWidget::state( int id ) const
{
    return satellites[ id ].state;
}

void SkyplotWidget::setState( int id, SatelliteState state )
{
    satellites[ id ].state = state;
    this->update();
}

QString SkyplotWidget::label( int id ) const
{
    return satellites[ id ].label;
}

void SkyplotWidget::setLabel( int id, const QString & label )
{
    satellites[ id ].label = label;
    this->update();
}

float SkyplotWidget::azimuth( int id ) const
{
    return satellites[ id ].az;
}

float SkyplotWidget::elevation( int id ) const
{
    return satellites[ id ].distance;
}

void SkyplotWidget::setAzimuth( int id, float az )
{
    satellites[ id ].az = az;
    this->update();
}

void SkyplotWidget::setElevation( int id, float el )
{
    satellites[ id ].distance = el;
    this->update();
}
//------------------w----------
//新添设置卫星大小
void SkyplotWidget::setStateSize(int id, float si)
{
    satellites[ id ].rsize = si;
    this->update();
}

QList< int > SkyplotWidget::ids( void ) const
{
    return satellites.keys();
}

SkyplotWidget::SatelliteState operator| (  SkyplotWidget::SatelliteState lhs, SkyplotWidget::SatelliteState rhs )
{
    return static_cast< SkyplotWidget::SatelliteState >(  static_cast< quint8 >( lhs ) | static_cast< quint8 >( rhs ) );
}
