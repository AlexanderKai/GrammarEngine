// -----------------------------------------------------------------------------
// File IMB_MAIN.H
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2004
//
// Content:
// ������ ��������� 3d �������. � ��������, ��� ������������ ������, � ���������
// ����������� �������� ������� ��������� ������� � ������������� ������.
// -----------------------------------------------------------------------------
//
// CD->13.07.95
// LC->21.09.04
// ------------

#if !defined( IMB_MAIN__H ) && !defined LEM_NOREAL
 #define IMB_MAIN__H

 #include <lem/quantors.h>
 #include <lem/qmatrix.h>
 #include <lem/render/imb_parr.h>
 #include <lem/render/imb_g3d.h>
 #include <lem/render/imb_g2d.h>
 #include <lem/render/imb_rgb.h>
 #include <lem/render/imb_coll.h>
 #include <lem/render/imb_scrb.h>

 namespace lem
 {
  namespace Render
  {

 /*******************************************************
  ������� ����������� ����������� ��� ��� ����������
  �����������, ������� �������� � ���������� ����������.
  ����������� ������������ �������� ������� ������ �
  ����������� ������� ������� (��������� ���������, �
  ������� ����� ����������� - a,b,c,h).
 ********************************************************/
 struct IMB_WireTriangle
 {
  int A,B,C;
  REAL a,b,c,h;

  IMB_WireTriangle(void) { A=B=C=0; a=b=c=h=0.; }
  IMB_WireTriangle(
                   int AA,
                   int BB,
                   int CC,
                   REAL aa=0.,
                   REAL bb=0.,
                   REAL cc=0.,
                   REAL hh=0.
                  )
  {
   A=AA; B=BB; C=CC;
   a=aa; b=bb; c=cc; h=hh;
  }
 };

 /*****************************************************************
  ������� ����� - ����� ����� ���������, ������������ ���
  ��������� ����������� �������. ��������� ������� ���������
  �������� ������.
 ******************************************************************/
 struct IMB_Segment
 {
  int A, B;

  IMB_Segment(void) { A=B=0; }
  IMB_Segment( int a, int b ) { A=a; B=b; }
 };

 /***********************************************************
  ������������������ ��� <�����������> ��� �������������
  ������ ��������. �������� ��������� ��������������
  ����������� ���������� ��� ��������� �������� ��� ���������
  ����������.
 ************************************************************/
 struct IMB_Triangle
 {
  REAL Nwx, Nwy, Nwz, Nwh; // ��������� ���������.

  REAL DXa,DYa,DZa;        // ���������� �������� ��������
  REAL DXb,DYb,DZb;        // � �������� ������������� (���
  REAL DXc,DYc,DZc;        // ���������� ������� ������������).

  int A,B,C;               // ������� ������ � ������ ������ ����������
                           // �������, ���� ������ ������������.

  #if !defined IMB_NORAY
  // ��� ����� ��������� ��������� �����������
  // ���� ������� ��������� ��������� �����, �������
  // ���������� ����������� - ��������� ������ � �������
  // �������.
  REAL x0,y0,z0,r2;
  #endif

  bool back; // ���� ����������� ������ � ������� ������������
             // �������, �� back=true, ��� ��������� ������ ��������
             // ������ ����� ��� ������������ ������.

  inline void SetBack( bool f ) { back=f; }

  IMB_Triangle(void)
  {
   A=B=C=0;

   DXa=DXb=DXc=Nwx=
   DYa=DYb=DYc=Nwy=
   DZa=DZb=DZc=Nwz=
   #if !defined IMB_NORAY
   x0=y0=z0=r2=
   #endif
   0.;

   back=false;
   return;
  }

  IMB_Triangle(
               int iA, int iB, int iC,
               REAL nx, REAL ny, REAL nz, REAL nh
              )
  {
   A=iA; B=iB; C=iC;

   DXa=DXb=DXc=Nwx = nx;
   DYa=DYb=DYc=Nwy = ny;
   DZa=DZb=DZc=Nwz = nz;

   back = nh<=0.;

   #if !defined IMB_NORAY
   x0=y0=z0=r2=0.;
   #endif
  }
 };

 /******************************************************************
  �������� ���������� ����� ��������� �����, ������������ ������
  � ������������� ����������.
 *******************************************************************/
 struct IMB_Lamp
 {
  REAL x, y, z;  // ������� ����������.
  REAL i;        // ������������� �������������.
  IMB_Lamp(void);
  IMB_Lamp( REAL X, REAL Y, REAL Z, REAL I );

  // ��� ����������� ���������.
  void apply( const RMatrix& mat );
 };

 /******************************************************************
  �������� ���������� ���������, ������������ ����������� �������.
 *******************************************************************/
 class IMB_Material
 {
  private:
   REAL M;         // ������������� ����������� ����
   REAL N;         // ������������ ���������
   IMB_RGBi color; // ������� ���� �����������
   REAL Opacity;   // ������������ ���������
   int Texture;    // ��� ��������
   bool self_lit;  // ������� ��������� �� �����������, ����� ������������
                   // ������� ���� ��������� (��������������).

  public:
   IMB_Material(void);
   IMB_Material(
                REAL BrightFactor,
                REAL MirrFactor,
                const IMB_RGBi Color,
                REAL OpaqueFactor=0.0, // �� ��������� ������������
                int Texture=UNKNOWN, // � ��� ��������
                bool SelfLit=false
               );

   inline const IMB_RGBi GetM(void) const { return M; }
   inline const IMB_RGBi GetN(void) const { return N; }
   inline const IMB_RGBi GetClr(void) const { return color; }
   inline REAL GetOpacity(void) const { return Opacity; }
   inline int GetTexture(void) const { return Texture; }
   inline bool IsSelfLit(void) const { return self_lit; }
 };

 /**********************************************************
   ����������� ����� �������������� ����� ������� ������
   ������ � ����� �������.
 ***********************************************************/
 struct IMB_Edge3di
 {
  int A,B;

  IMB_Edge3di(void) { A=B=0; }
  IMB_Edge3di( int a, int b ) { A=a; B=b; }
 };

 class IMB_Renderer;
 class IMB_HIP_Scaler;

 /*****************************************************************
  ����� 3D ������, ������������� ����������� ������� �������������,
  ������������ ��� �����������.

  ���������� ������ �������� � ������� ������� ���������. ������
  ����������� ����������� ��������� ����� � ��� �������� � ���������
  ��������, ���������� �� ������.

  ������� �������� ����������� �������� ��������. ����� ������
  Unload() �������� � �������� ����������� �������� tri, vertex �
  ivertex � �������������� ����. ��� ���� ������������� ����������
  ��� ������. �����, ������ ������������ ��� ������������� �������
  ������� ���� ������� ���������, �� ��� �� ������ �������� ��
  ���� (����� ������ IsSwapped()). ���� ���, �� ������ �����������
  ������� Build(), � ����� �������� �������������� ���������
  �������� ���������  ������� Unload().
 *******************************************************************/
 class IMB_BaseBody
 {
  protected:
   IMB_PenHolder pen; // ��� ����������� �������.
   bool autodel_pen; // ���� �������� ������ ���� ������������� �����.

   bool redraw_edges;                 // ���� ����� ���������� �������� ����� ���������� pen.
   bool changed;                      // ��������� �������� ������� ���������.
   IMB_Material mat;                  // �������� ��������� �����������.
   MCollect<IMB_Point3d>  vertex;  // ������ ������.
   MCollect<IMB_Point3d>  ivertex; // ������ ��������������� ������.
   MCollect<IMB_Triangle> tri;     // ������ �������������.

   // ������ ������������ �����. �� ������������ ��� �������� ��������
   // ������ �������� ������������ �����������. ��� ����� �����������
   // ��� ���� ������ ������������ ����� ��������.
   MCollect<IMB_Edge3di> edges;

   void RegisterSegment(
                        IMB_VertexList *SEGMENT,
                        int A, int B,
                        REAL a, REAL b, REAL c,
                        REAL CosTreshold
                       );

   int key;             // �������� ������ (����������) ����.
   REAL X0,Y0,Z0;       // ���������� ��������������� ������.
   REAL R2;             // ������� ������� ����������� ��������.

   bool visible;        // ���� ����� ���� ��������� (==false).

  public:
   REAL XMIN,YMIN,ZMIN; // ���������� ����� ��������������� ���������������.
   REAL XMAX,YMAX,ZMAX;

  public:
   IMB_BaseBody( int Key=UNKNOWN );

   virtual ~IMB_BaseBody(void);

   void dirty( bool f=true ) { changed=f; }
   bool IsChanged(void) const { return changed; }

   inline const IMB_PenHolder& GetPen(void) const { return pen; }
   inline IMB_BaseBody& operator<<( const IMB_PenHolder &Pen )
   {
    autodel_pen=false;
    pen=Pen;
    return *this;
   }

   inline void DoHide(void) { visible=false; }
   inline void DoShow(void) { visible=true;  }
   inline bool IsVisible(void) const { return visible; }

   virtual int nVertex(void) const { return vertex.size(); }
   virtual int nTri(void)    const { return tri.size();    }
   virtual int nEdge(void)   const { return edges.size();  }

   virtual void Create(void);
   virtual void CreateEdges( const REAL CosTreshold, const bool DrawBack );

   virtual void apply( const RMatrix &T );

   virtual IMB_Triangle& GetTriangle( int i ) { return tri[i]; }
   virtual IMB_Point3d& GetVertex( int i ) { return vertex[i]; }
   virtual IMB_Point3d& GetiVertex( int i ) { return ivertex[i]; }
   virtual IMB_Edge3di& GetEdge( int i ) { return edges[i]; }

   const IMB_Material& GetMaterial(void) const { return mat; }
   void SetMaterial( const IMB_Material& m ) { mat=m; }

   inline void SetKey( int Key ) { key=Key; }
   inline int GetKey(void) const { return key; }

   inline REAL GetX0(void) const { return X0; }
   inline REAL GetY0(void) const { return Y0; }
   inline REAL GetZ0(void) const { return Z0; }
   inline const IMB_Point3d Get0(void) const { return IMB_Point3d(X0,Y0,Z0); }
   const IMB_Point3d CalcCenter(void) const;

   inline REAL GetR2(void) const { return R2; }
   virtual void Clear(void);

   void AddEdge( const IMB_Edge3di &e );
   void AddVertex( const IMB_Point3d &v );
   void AddFacet( const IMB_Triangle &t );

   // ���������� true, ���� ���� �� ����� ��������� �������������, �
   // ������ - ����������� ������, ����� ������� ��� ��������� (�����
   // ray tracer'�) ������ �������� ����������� ������.
   virtual bool IsWired(void) const { return false; }

   inline bool DoRedrawEdges(void) const { return redraw_edges; }

   // ������� ���� ���������� false, � ������ ������, �� ���� ���������
   // �� ������ ���, ���������� true.
   virtual bool IsAssembly(void) const { return false; }

   virtual void RenderSelf(
                           IMB_Renderer *rend,
                           IMB_VideoBuffer *hdc,
                           const IMB_HIP_Scaler &scaler
                          ) const {};

 };

 /*****************************************************
  ����� ����������� �������.
 ******************************************************/
 class IMB_BaseWireBody : public IMB_BaseBody
 {
  public:
   IMB_BaseWireBody( int Key=UNKNOWN ):IMB_BaseBody(Key){};

   virtual void CreateEdges( REAL CosTreshold, bool DrawBack ){};
   virtual bool IsWired(void) const { return true; }
 };

 class IMB_Assembly : public IMB_BaseBody
 {
  private:
   IMB_Ptr_NC_Collect<IMB_BaseBody> list; // ������ ������.

  public:
   IMB_Assembly( int Key=UNKNOWN );
   virtual ~IMB_Assembly(void);

   virtual bool IsAssembly(void) const { return true; }
   virtual void Create(void);
   virtual void CreateEdges( REAL CosTreshold, bool DrawBack );
   virtual void apply( const RMatrix &T );
   virtual void Clear(void);

   inline void Add( IMB_BaseBody *toAdd ) { list.push_back(toAdd); }
   inline int GetnBody(void) const { return list.size(); }
   inline const IMB_BaseBody& GetBody( int i ) const
   { return *list[i]; }

   inline IMB_BaseBody* GetBodyPtr( int i )
   { return list[i]; }

   IMB_BaseBody* FindBody( int Key );
 };

 class IMB_Body;

 // ----------------------------------
 // ������������� ������� ������������
 // ��� ����� � ������������ � �������
 // �������.
 // ----------------------------------
 struct IMB_BodyVertex
 {
  REAL x,y,z;
  REAL nx, ny, nz;

  IMB_BodyVertex(void);

  IMB_BodyVertex(
                 REAL NX,
                 REAL NY,
                 REAL NZ
                );

  IMB_BodyVertex(
                 REAL X,
                 REAL Y,
                 REAL Z,
                 REAL NX,
                 REAL NY,
                 REAL NZ
                );

  void Store( IMB_Body &b ) const;
 };

 typedef IMB_BodyVertex IMB_Normal;

 class IMB_Body : public IMB_BaseBody
 {
  public:
   IMB_Body( int Key, const IMB_Material &m );

   void WriteVertex( REAL x, REAL y, REAL z );
   void WriteFacet(
                   int A, int B, int C,
                   const IMB_Normal &n1,
                   const IMB_Normal &n2,
                   const IMB_Normal &n3
                  );

   void WriteTriFacet( int A, int B, int C );

   void AddVertex( const IMB_Point3d& v );
   void AddTriangle( const IMB_Triangle& t );
 };

 extern IMB_Body* imb_load_body_x( const char *filename );
 extern IMB_Body* imb_load_body( const char *filename );

 class IMB_WireBody : public IMB_BaseWireBody
 {
  public:
   IMB_WireBody(
                int Key,
                const IMB_Material &m
               );

   void AddVertex( IMB_Point3d& v );
 };

 // **********************************************************************

 // ������ ��� ����������� ����� ������� ��� 3d ��������.
 // �� ������ ������ ��������� �� ������� � �������, ��
 // ������� � �� ��������� ��.
 class IMB_XYView : public IMB_Body
 {
  private:
   RMatrix *matrix;
   bool do_del; // ����� �� ������������� ������� ������ matrix?

   IMB_Point3d org; // ��� �������� ������ ��������� (�������� �����������)
   REAL KX, KY, KZ; // �������������� ������� ��� ��������.
   IMB_Point3d retp;
   IMB_Triangle rett;
   IMB_Edge3di retr;

   int ni,nj,i0,j0,nvertex,nedge,ntri;
   REAL XM,YM,ZM,Zmin,Zmax;
   REAL OffX0, OffY0, OffZ0;

   void SetMatrix( RMatrix *m );

  public:
   IMB_XYView(
              RMatrix *m,
              bool DoDel,
              const IMB_Material &mat,
              int Key=UNKNOWN
             );

   virtual ~IMB_XYView(void);

   virtual void Create(void);

   inline void SetOrg( const IMB_Point3d &Org ) { org=Org; }
   inline const IMB_Point3d GetOrg(void) const { return org; }
   inline void SetScaling( REAL kx, REAL ky, REAL kz )
   { KX=kx; KY=ky; KZ=kz; }

   virtual int nVertex(void) const { return nvertex; }
   virtual int nTri(void)    const { return ntri; }
   virtual int nEdge(void)   const { return nedge; }

   virtual IMB_Triangle& GetTriangle( int i );
   virtual IMB_Point3d&  GetVertex(  int i );
   virtual IMB_Point3d&  GetiVertex( int i );
   virtual IMB_Edge3di&  GetEdge( int i );

   virtual void Clear(void);
   virtual void CreateEdges( const REAL CosTreshold, bool DrawBack ){};
 };

 // **********************************************************************

 class IMB_GenericCyl : public IMB_Body
 {
  public:
   IMB_GenericCyl(
                  int NOX, int NB,
                  REAL Gamma,
                  bool plate_butt,
                  const IMB_Material &m,
                  int Key=UNKNOWN
                 );
 };

 class IMB_Cylinder : public IMB_Body
 {
  public:
   IMB_Cylinder(
                int n,
                REAL x, REAL y, REAL z,
                REAL R, REAL H,
                const IMB_Material &m,
                int Key=UNKNOWN
               );
  };

 class IMB_Tube : public IMB_Body
 {
  public:
   IMB_Tube(
            int n,
            REAL x, REAL y, REAL z,
            REAL Rout, REAL Rin, REAL H,
            const IMB_Material &m,
            int Key=UNKNOWN
           );
 };

 class IMB_Vederko : public IMB_Body
 {
  public:
   IMB_Vederko(
               int n,
               REAL x, REAL y, REAL z,
               REAL Rb, REAL Rt, REAL H,
               const IMB_Material &m,
               int Key=UNKNOWN
              );
 };


 class IMB_Cone : public IMB_Body
 {
  public:
   IMB_Cone(
            int n,
            REAL x, REAL y, REAL z,
            REAL R, REAL H,
            const IMB_Material &m,
            int Key=UNKNOWN
           );
 };

 class IMB_Box : public IMB_Body
 {
  public:
   IMB_Box(
           REAL x, REAL y, REAL z,
           REAL dx, REAL dy, REAL dz,
           const IMB_Material &m,
           int Key=UNKNOWN
          );
 };

 class IMB_Sphere : public IMB_Body
 {
  public:
   IMB_Sphere(
              REAL x0, REAL y0, REAL z0,
              REAL R,
              const IMB_Material &m,
              int Key=UNKNOWN
             );
 };

 class IMB_Globe : public IMB_Body
 {
  public:
   IMB_Globe(
             int n, int m,
             REAL x0, REAL y0, REAL z0,
             REAL R,
             const IMB_Material &mat,
             int Key=UNKNOWN
            );
 };

 class IMB_Dodecahedron : public IMB_Body
 {
  public:
   IMB_Dodecahedron(
                    REAL x0, REAL y0, REAL z0,
                    REAL a,
                    const IMB_Material &m,
                    int Key=UNKNOWN
                   );
 };

 class IMB_Icosahedron : public IMB_Body
 {
  public:
   IMB_Icosahedron(
                   REAL x0, REAL y0, REAL z0,
                   REAL a,
                   const IMB_Material &m,
                   int Key=UNKNOWN
                  );
 };

 class IMB_Torus : public IMB_Body
 {
  public:
   IMB_Torus(
             int n,
             REAL x0, REAL y0, REAL z0,
             REAL R, REAL r,
             const IMB_Material &m,
             int Key=UNKNOWN
            );
 };

 class IMB_GeneralExtruder : public IMB_Body
 {
  protected:
   virtual void GetContour( int inode, MCollect<IMB_Point2d> &c );
   virtual void BuildUp( const MCollect<IMB_Point3d> &XYZ );

  public:
   IMB_GeneralExtruder(
                       const IMB_Material &mat,
                       int Key=UNKNOWN
                      );
  };

 class IMB_Cable : public IMB_GeneralExtruder
 {
  protected:
   MCollect<IMB_Point3d> XYZ;
   MCollect<IMB_Point2d> Contour;

   virtual void GetContour( int inode, MCollect<IMB_Point2d> &c );
   virtual void Create(void);

  public:
   IMB_Cable(
             const IMB_Material &mat,
             int Key=UNKNOWN
            ):IMB_GeneralExtruder(mat,Key) {};

   IMB_Cable(
             int n,
             REAL R,
             const MCollect<IMB_Point3d> &xyz,
             const IMB_Material &mat,
             int Key=UNKNOWN
            );

   IMB_Cable(
             int n,
             REAL R,
             const IMB_Material &mat,
             int Key=UNKNOWN
            );

   IMB_Cable(
             const MCollect<IMB_Point2d> &Section,
             const MCollect<IMB_Point3d> &xyz,
             const IMB_Material &mat,
             int Key=UNKNOWN
            );
  };

 class IMB_Spring : public IMB_Cable
 {
  public:
   IMB_Spring(
              REAL x0,
              REAL y0,
              REAL z0,
              REAL h,
              REAL nt,
              int N_0_node,
              int N_c_node,
              REAL r,
              REAL R0,
              REAL R1,
              const IMB_Material &mat,
              int Key=UNKNOWN
             );
  };

 class IMB_Ribbon : public IMB_Cable
 {
  public:
   IMB_Ribbon(
              const MCollect<IMB_Point3d> &path,
              REAL width,
              REAL thickness,
              IMB_Material &mat,
              int Key=UNKNOWN
             );
  };

 class IMB_WaveRibbon : public IMB_Cable
 {
  public:
   IMB_WaveRibbon(
                  const IMB_Point3d &org,
                  REAL Height,
                  REAL WavePeriod,
                  REAL WaveAmplitude,
                  int nNodePoint,
                  REAL width,
                  REAL thickness,
                  const IMB_Material &mat,
                  int Key=UNKNOWN
                 );
  };


  class IMB_ScrewThread : public IMB_Body
  {
   private:
    void p1( MCollect<int> &facet, int i );
    void p1e( MCollect<int> &facet, int i );
    void p3e(
             MCollect<int> &facet,
             int i,
             int j,
             int k
            );
    void p4e(
             MCollect<int> &facet,
             int i,
             int j,
             int k,
             int l
            );
    void pr(
            MCollect<int> &facet,
            int a,
            int b
           );
    void StoreFacet( MCollect<int> &facet );

   public:
    IMB_ScrewThread(
                    REAL major,
                    REAL minor,
                    REAL pitch,
                    REAL length,
                    REAL X0,
                    REAL Y0,
                    REAL Z0,
                    int k,
                    const IMB_Material &m,
                    int Key=UNKNOWN
                   );
  };

 class IMB_Surface : public IMB_Body
 {
  public:
  IMB_Surface(
              int m,
              int n,
              const REAL *xx,
              const REAL *yy,
              const REAL *zz,
              int M,
              int N,
              const IMB_Material &Mat,
              int Key
             );
  };

 class IMB_Extruder : public IMB_Body
 {
  protected:
   void Build(
              int NPOLY,
              const REAL *x,
              const REAL *y,
              REAL H
             );

   IMB_Extruder(
                const IMB_Material &Mat,
                int Key=UNKNOWN
               );

  public:
   IMB_Extruder(
                int NPOLY, // ����� ����� � 2d ��������
                const REAL *x,   // ���������� ������ ��������
                const REAL *y,
                REAL H,    // ������ ����������� ����
                const IMB_Material &Mat,
                int Key=UNKNOWN
               );
  };

  class IMB_Symbol : public IMB_Extruder
  {
   public:
    IMB_Symbol(
               FILE *file,
               REAL x0,
               REAL y0,
               REAL z0,
               REAL wx,
               REAL wy,
               REAL H,
               const IMB_Material &Mat,
               int Key=UNKNOWN
              );
  };

  class IMB_WireBox : public IMB_WireBody
  {
   public:
    IMB_WireBox(
                const IMB_Box3d &box,
                int Key=UNKNOWN
               );
  };

 class IMB_Camera
 {
  private:
   // ������ ������� � ����� (0,0,0)!
   IMB_Point3d pos;        // ��������� ������ - ������� ����������.

   REAL xm,ym,zm; // ������� �������� ������� ��������� � �������� - ���� ������������.
   REAL xemin,yemin,zemin; // ��� ���� ������������.
   REAL xemax,yemax,zemax; // ��� ���� ������������.

   REAL Rt;            // ������ ������� ������ ������, ������������ �������.
   REAL zoom_x,zoom_y; // ������� zooming'�.
   REAL ExposeTime;    // ����� ����������.

   IMB_Box3d transfoc; // �������, ������������ �������.

  public:
   IMB_Camera(void);

   inline const IMB_Point3d& GetPos(void) const { return pos; }

   inline const REAL GetExposTime(void) const { return ExposeTime; }

   void SetExposTime( REAL et );
   void AddExpos( REAL dt );

   inline void Move( const Matrix4x4& T ) { pos*=T; }
   inline void Set( const IMB_Point3d& to ) { pos=to; }

   void SetZooming( REAL zx, REAL zy );
   inline REAL GetZooming_X(void) const { return zoom_x; }
   inline REAL GetZooming_Y(void) const { return zoom_y; }

   void SetTransfoc( REAL RT );
   void SetTransfoc( const IMB_Box3d &Box );

   inline REAL GetRt(void) const { return Rt; }
   inline const IMB_Box3d& GetTransfoc(void) const { return transfoc; }
   inline bool NeedTransfocCompute(void) const { return xm==0.; }

   inline REAL GetTransfoc_XM(void) const { return xm*zoom_x; }
   inline REAL GetTransfoc_YM(void) const { return ym*zoom_y; }
   inline REAL GetTransfoc_ZM(void) const { return zm;        }

   inline REAL GetTransfoc_XEMIN(void) const { return xemin*zoom_x; }
   inline REAL GetTransfoc_YEMIN(void) const { return yemin*zoom_y; }
   inline REAL GetTransfoc_ZEMIN(void) const { return zemin;        }

   inline REAL GetTransfoc_XEMAX(void) const { return xemax*zoom_x; }
   inline REAL GetTransfoc_YEMAX(void) const { return yemax*zoom_y; }
   inline REAL GetTransfoc_ZEMAX(void) const { return zemax;        }

   inline void SetTransfoc_XYZ(
                               REAL Xm,
                               REAL Ym,
                               REAL Zm,
                               REAL Xemin,
                               REAL Yemin,
                               REAL Zemin,
                               REAL Xemax,
                               REAL Yemax,
                               REAL Zemax
                              )
   {
    xm=Xm; ym=Ym; zm=Zm;
    xemin=Xemin; yemin=Yemin; zemin=Zemin;
    xemax=Xemax; yemax=Yemax; zemax=Zemax;
   }
 };

 /****************************************************************
  �����-���������, �������� ��������� ������������ �����, ������
  �������� ��� �����������, ������ ���������� ����� � ���� ��������
  ������.
 ****************************************************************/
 class IMB_Scene
 {
  public:
   IMB_Ptr_NC_Collect<IMB_BaseBody> body; // ������ �������� ��� �����������.
   MCollect<IMB_Lamp> lamp;           // ��� ��������� �����.
   REAL Ldiff;             // ������������� �������� ���������� ���������.

   IMB_Camera Camera; // ����� ������.
   bool camera_moved; // ������, ������� �������� ��������, �������������...

  public:
   IMB_Scene(void);

   inline int nBody(void) const { return body.size(); }
   inline int nLamp(void) const { return lamp.size(); }

   IMB_Scene& operator<<( IMB_BaseBody *b );
   IMB_Scene& operator<<( const IMB_Lamp &l );

   IMB_BaseBody* FindBody( int Key );
   bool Delete( int Key );
   inline IMB_BaseBody& GetBody( int i ) { return *body[i]; }

   inline IMB_Lamp& GetLamp( int i ) { return lamp[i]; }

   inline const IMB_Camera& GetCamera(void) const { return Camera; }
   inline IMB_Camera* GetCameraPtr(void) { return &Camera; }
   inline void MoveCamera( const Matrix4x4& T )
   {
    Camera.Move(T);
    Dirty();
    camera_moved = true;
    return;
   }

   inline void SetCamera( const IMB_Point3d& to )
   {
    Camera.Set(to);
    Dirty();
    camera_moved = true;
    return;
   }

   inline void SetCamera( const IMB_Camera &c )
   {
    Camera=c;
    camera_moved = true;
    Dirty();
    return;
   }

   inline void CameraHasMoved( bool f ) { camera_moved=f; }
   inline bool HasCameraMoved(void) const { return camera_moved; }

   inline REAL GetBacklight(void) const { return Ldiff; }
   void SetBacklight( const REAL ldiff );

   void Dirty(void);
   void RubOff(void);
 };

 extern void imb_DecomposePolygon(
                                  const MCollect<IMB_Point3d> &verteces,
                                  MCollect<IMB_Triangle> &facets

                                   );
  } // namespace Render
 } // namespace lem

#endif // !defined IMB_MAIN__H
// ---------------------------- End Of File [IMB_MAIN.H] -----------------------
