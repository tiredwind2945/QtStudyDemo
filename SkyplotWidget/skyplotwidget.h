
#ifndef SKYPLOT_WIDGET_H
#define SKYPLOT_WIDGET_H
#include <QMap>
#include <QTimer>
#include <QWidget>

#define MY_PI  3.141593
class  SkyplotWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY( float  marginScale       READ marginScale     WRITE setMarginScale    )
    Q_PROPERTY( float  satelliteScale    READ satelliteScale  WRITE setSatelliteScale )
    Q_PROPERTY( float  fontScale         READ fontScale       WRITE setFontScale      )
    Q_PROPERTY( QColor gridColor         READ gridColor       WRITE setGridColor      )
    Q_PROPERTY( QColor gridTextColor     READ gridTextColor   WRITE setGridTextColor  )
    Q_PROPERTY( int    gridWidth         READ gridWidth       WRITE setGridWidth      )
    Q_PROPERTY( int    ellipses          READ ellipses        WRITE setEllipses       )
    Q_PROPERTY( int    crosses           READ crosses         WRITE setCrosses        )
    Q_PROPERTY( int    textMargin        READ textMargin      WRITE setTextMargin     )
    Q_PROPERTY( int    flashIntervall    READ flashIntervall  WRITE setFlashIntervall )
    Q_PROPERTY( bool   withGridLabels    READ withGridLabels  WRITE setWithGridLabels )
    Q_PROPERTY( bool   antialiased       READ antialiased     WRITE setAntialiased    )

public:
    enum SatelliteState : quint8 {
        Invisible   = 0x00,
        Visible     = 0x01,
        HalfVisible = 0x02,
        Marked      = 0x04,
        Flashing    = 0x08 };
    Q_ENUMS( SatelliteState )

    explicit SkyplotWidget( QWidget *parent = nullptr );

    SkyplotWidget(const SkyplotWidget & spw )             = delete;
    SkyplotWidget& operator= (const SkyplotWidget & spw)  = delete;
    SkyplotWidget( SkyplotWidget && rhs )                 = delete;
    SkyplotWidget& operator=( SkyplotWidget && rhs )      = delete;
    ~SkyplotWidget()                                      = default;

    void  setMarginScale    ( float          scale ){ p_marginScale    = scale;       this->update(); }
    void  setSatelliteScale ( float          scale ){ p_satScale       = scale;       this->update(); }
    void  setFontScale      ( float          scale ){ p_fontScale      = scale;       this->update(); }
    void  setGridColor      ( const QColor & color ){ p_gridColor      = color;       this->update(); }
    void  setGridTextColor  ( const QColor & color ){ p_gridTextColor  = color;       this->update(); }
    void  setGridWidth      ( int            width ){ p_gridWidth      = width;       this->update(); }
    void  setEllipses       ( int               no ){ p_ellipses       = no;          this->update(); }
    void  setCrosses        ( int               no ){ p_crosses        = no;          this->update(); }
    void  setTextMargin     ( int           margin ){ p_textMargin     = margin;      this->update(); }
    void  setFlashIntervall ( int        intervall ){ p_flashIntervall = intervall;   this->update(); }
    void  setWithGridLabels ( int       withLabels ){ p_withGridLabels = withLabels;  this->update(); }
    void  setAntialiased    ( int      antialiased ){ p_antialiased    = antialiased; this->update(); }

    float          marginScale       ( void ) const { return p_marginScale;    }
    float          satelliteScale    ( void ) const { return p_satScale;       }
    float          fontScale         ( void ) const { return p_fontScale;      }
    const QColor & gridColor         ( void ) const { return p_gridColor;      }
    const QColor & gridTextColor     ( void ) const { return p_gridTextColor;  }
    int            gridWidth         ( void ) const { return p_gridWidth;      }
    int            ellipses          ( void ) const { return p_ellipses;       }
    int            crosses           ( void ) const { return p_crosses;        }
    int            textMargin        ( void ) const { return p_textMargin;     }
    int            flashIntervall    ( void ) const { return p_flashIntervall; }
    int            withGridLabels    ( void ) const { return p_withGridLabels; }
    int            antialiased       ( void ) const { return p_antialiased;    }

    QColor         innerColor     ( int id ) const;
    QColor         outerColor     ( int id ) const;
    QColor         fontColor      ( int id ) const;
    SatelliteState state          ( int id ) const;
    QString        label          ( int id ) const;
    float          azimuth        ( int id ) const;
    float          elevation      ( int id ) const;

    QList< int >  ids( void ) const;

public slots:

    void insert( int   id,
                 float az = 0,
                 float distance = 90.0,
                 float rsize = 0.03,
                 const QString & label      = QString(""),
                 const QColor  & outerColor = Qt::red,
                 const QColor  & innerColor = Qt::lightGray,
                 const QColor  & fontColor  = Qt::black,
                 SatelliteState  state      = SatelliteState::Visible );

    void remove( int id );

    void insertLine( int id,
                     const QPoint p1,
                     const QPoint p2,
                     const QColor & lineColor = Qt::cyan,
                     SatelliteState state     = SatelliteState::Visible );

    bool contains( int id ) const;

    void setInnerColor  ( int id, const QColor & c       );
    void setOuterColor  ( int id, const QColor & c       );
    void setFontColor   ( int id, const QColor & c       );
    void setState       ( int id, SatelliteState state   );
    void setLabel       ( int id, const QString & label  );
    void setAzimuth     ( int id, float az               );
    void setElevation   ( int id, float el               );
    //------- W --- start -----
    void setStateSize   ( int id, float si );

    void setLineState   ( int id, SatelliteState state);
    void setLinePoint   ( int id, const QPoint p1, const QPoint p2);
    void setLineColor   ( int id, const QColor & c);
    void setLinePoint2  ( int id, const QPoint p2);
    //------------ end ------------------------------------------

    void setMonitorScope(double d); //设置监视范围
protected:
#ifndef SKYPLOT_QML_SUPPORT
    void paintEvent(QPaintEvent *event);

    /**
     * @brief calculatePos : 根据方位角和距离，计算出X和Y的坐标
     * @param az ： 方位角
     * @param distance ： 距离
     * @param x ： X轴坐标
     * @param y ： Y轴坐标
     * @return ： 标记坐标计算是否有误
     */
    bool calculatePos(const double &az , const double &distance, double &x ,  double &y);

    bool equal(double num1,double num2);

#else
    void paint(QPainter *painter);
#endif

private:
    bool      flash;
    QTimer    flashTimer;

    float     p_marginScale;
    float     p_satScale;
    float     p_fontScale;
    QColor    p_gridColor;
    QColor    p_gridTextColor;
    int       p_gridWidth;
    int       p_ellipses;
    int       p_crosses;
    int       p_textMargin;
    int       p_flashIntervall;
    bool      p_withGridLabels;
    bool      p_antialiased;

    double    mMonitorScope;

    typedef struct _Satellite
    {
        QString  label;
        QColor   innerColor;
        QColor   outerColor;
        QColor   fontColor;
        float    az;
        float    distance;
        float    rsize;
        SatelliteState  state;
    } Satellite;

    QHash< int, Satellite > satellites;

    //--------------- W --- start ---------
    // line
    typedef struct _Myline
    {
        QColor lineColor;
        QPoint point1;
        QPoint point2;
        SatelliteState lineState;
    }Myline;

    QHash< int, Myline> indicatrix;
    int           m_pieRotate;     //扇形旋转区域
    //   QRect         m_drawArea;      //绘制区域
    QTimer        m_PieSpeed;
    //---------------------- W --- end -------

private slots:
    void change_flash( void );
    void pie_speed( void );
};

SkyplotWidget::SatelliteState operator| (  SkyplotWidget::SatelliteState lhs, SkyplotWidget::SatelliteState rhs );

#endif
