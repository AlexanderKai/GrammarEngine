// -----------------------------------------------------------------------------
// File POLYNOMIAL.H
//
// (c) Koziev Elijah
//
// Content:
// ����� BasePolynome - �������������� ����������, ��������������� �������� ���
// ����.
// -----------------------------------------------------------------------------
//
// CD->04.07.1995
// LC->16.07.2008
// --------------

#ifndef LEM_POLYNOME__H
#define LEM_POLYNOME__H
#pragma once

 #include <lem/config.h>
 #include <lem/math/real.h>
 #include <lem/stl.h>
 #include <lem/qarray.h>

 namespace lem
 {
  /***************************************************************************

    ����� BasePolynome ��� ������������� �������������� �����������.
    ������� ����������� ����� �������� � ���������� ������������� ��� ��������
    x. ��������������, ��� ������������ ������������ ������� ���� REAL.

    ������� �������� ��������, ��� ������� ������� ORDER ����� ��������
    (ORDER+1) ��������� �������������.

    ����� ������������� �������� ��������, ���-��: ���������� �������� ��������
    ��� ��������� x �� ����� �������, ��������, ���������, ������������ �
    ������� ���������, ������ �����������, ������ ��������������� ���������.

    ����������: ��������� C++ compiler ��������� AT&T Cfront 3.0 ���
                ����.

    �����: ������������ ������ ����������� C-������.

    ������: ����� ������ ��� ������������ ���������� �����������.

    ���������:
              1. ��������� � ������������� �������������� ����� �������������
                 �������� []. ������, ������������ ����� ������, ������������
                 ������� ����, ����������� ��� ���� ���������� �������.


              2. � ������ LEM_DEBUGGING=1 �������������� ������������ ��������
                 � ��������� ������� operator[]. ��� ��������� ������
                 �������� ������������� ����������� � ���������� �����������.

  *****************************************************************************/

  #define BPT BasePolynome<T>

  template < class T >
  class BasePolynome : public BaseArray<T>
  {
   public:
    #if defined __MINGW__ || defined LEM_GNUC 
    inline const typename BaseArray<T>::value_type* get_Container(void) const
    { return BaseArray<T>::get_Container(); }
    #endif  
   
   public:

   BasePolynome(void):BaseArray<T>(1)
   {
    BaseArray<T>::front() = T(0);
    return;
   }

   BasePolynome( int N, const T *c=NULL ):BaseArray<T>(N+1)
   {
    if( c )
     for( int i=Order(); i>=0; i-- )
      BaseArray<T>::operator[](i)=c[i];

    return;
   }

   #if defined __MINGW__ || defined LEM_GNUC
   inline typename BaseArray<T>::size_type size(void) const { return BaseArray<T>::size(); }    
   inline const typename BaseArray<T>::value_type& get( typename BaseArray<T>::size_type i ) const { return BaseArray<T>::get(i); }    
   #endif         
  
   // **************************************
   // One-item polynomial has order=0 !!!
   // **************************************
   inline int Order(void) const { return CastSizeToInt(size())-1; }

   const T max_abs_coef(void) const;

   BPT& normalize(void);
   BPT& anormalize(void);
   BPT& reduce(void);
   BPT& reduce(int);

   const T eval( const T x ) const;

   BPT& prime(void);
   BPT& prime( int l );

   BPT& integrate(void);
   BPT& integrate( int l );

   BPT& operator += ( const BPT& d );
   BPT& operator += ( const T a );

   BPT& operator -  (void);
   BPT& operator -= ( const BPT& d );
   BPT& operator -= ( const T a );

   BPT& operator /= ( const BPT& d );
   BPT& operator /= ( const T k );

   BasePolynome& operator %= ( const BPT& );

   BasePolynome& operator *= ( const BPT& d );
   BasePolynome& operator *= ( const T a );

   const BPT operator*( const BPT& b ) const;
   const BPT operator*( const T a ) const;

  };

  template < class T >
  inline BPT buildpoly( const T a0 )
  {
   BPT p;
   p[0]=a0;
   return p;
  }

  template < class T >
  inline const T poly2(
                       const T x,
                       const T a0,
                       const T a1,
                       const T a2
                      )
  { return (a2*x+a1)*x+a0; }

  template < class T >
  inline const T poly3(
                       const T x,
                       const T a0,
                       const T a1,
                       const T a2,
                       const T a3
                      )
  { return ((a3*x+a2)*x+a1)*x+a0; }

  template < class T >
  inline const T poly4(
                       const T x,
                       const T a0,
                       const T a1,
                       const T a2,
                       const T a3,
                       const T a4
                      )
  { return (((a4*x+a3)*x+a2)*x+a1)*x+a0; }


  // ***********************************************************************
  // ���������� ������������ �� ���������� �������� ����������� � ��������.
  // ************************************************************************
  template < class T >
  inline const T BPT::max_abs_coef(void) const
  {
   T ma(0);
   for( int i=0; i<size(); i++ )
    ma = lem::max( ma, abs( BaseArray<T>::get_Container()[i]) );

   return ma;
  }


  // ---------------------------------------------------------------------
  // ���� ��� ������� �������� ����� ������� ������������, ���������
  // �������������� ������� ��������, ����� ��������� � ���������� �����
  // �������� ��� ������.
  // --------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::reduce(void)
  {
   const int nold=size();
   const T zero = T(max_abs_coef()) * min(*this);

   int nn = size();
   for( int i=nold-1; i>=0; i--, nn-- )
    if( abs( BaseArray<T>::get_Container()[i])>zero )
     break;

   if(nn<0) nn=0;

   BaseArray<T>::resize(nn);
   return *this;
  }

  template < class T >
  inline BPT& BPT::reduce( int k )
  {
   BaseArray<T>::resize( k>=0 ? k+1 : 1 );
   return *this;
  }

  // -------------------------------------------------------------------
  // ������������ ��������, �� ���� ���������� ��� � ����, ����� �����
  // ������� �����.==1. ��� ��������� ��� �������� ������ ��������������
  // ����������� � ������������ ��������!
  // -------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::normalize(void)
  {
   const T ai = get_Container()[ Order() ];

   get_Container()[Order()]=T(1);

   for( int i=Order()-1; i>=0; i-- )
    get_Container()[i] /= ai;

   return *this;
  }

  // **********************************************************************
  // ���������� �������� �������� ��� ��������� x �� ����� �������.
  //
  // This function evaluates a complex polynomial with real coeffieicents.
  // **********************************************************************
  template < class T >
  inline const T BPT::eval( const T x ) const
  {
   T f = std::vector<T>::operator[](Order());

   for( int i=Order()-1; i>=0; i-- )
    f = x*f + std::vector<T>::operator[](i);

   return f;
  }

  // ------------------------------------------------------------------------
  // ������� ������ ����������� ��������.
  //
  // This function will differentiate a single variable polinomial.
  //
  // ���������� ������� ������� �� ������� ������ ���������. ���� ��������
  // ������� ��� ����� ������� 0, �� ���� ��� ������, �� ������������ �������
  // �������� �������, ���������� 0.
  // ------------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::prime(void)
  {
   if(!Order())
    {
     BaseArray<T>::front()=T(0);
     return *this;
    }

   for( int i=0; i<Order(); i++ )
    BaseArray<T>::operator[](i) = T( BaseArray<T>::operator[](i+1))*T(i+1);

   BaseArray<T>::resize( size()-1 );

   return *this;
  }

  // -------------------------------------------------------------------
  // ������������ ����������� ��������� ������� l ������� �������������
  // �����������������. ��������� ����� ��������������, ������
  // ������������ ���������� �� ���� ������.
  // -------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::prime( int l )
  {
   for( int i=l-1; i>=0; i-- )
    prime();

   return *this;
  }

  // -------------------------------------------------------------------------
  // �������������� �������� �� ��������. �������� ������� ������� �� �������
  // ��������, ������ ��������.
  //
  // This function computes the definite integral of any single variable
  // polynomial.
  // -------------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::integrate(void)
  {
   reduce();

   if( !Order() && BaseArray<T>::front()==T(0) )
    return *this;

   BPT res( Order()+1, NULL );

   for( int i=0; i<=Order(); i++ )
    res.get_Container()[i+1] = T(get_Container()[i])/T(i+1);

   return (*this=res);
  }

  // ----------------------------------------------------------------------
  // ���������� �������� ��������������� ��������� � ������� �������������
  // �������������� l ���.
  // ----------------------------------------------------------------------
  template < class T >
  inline BPT& BPT::integrate( int l )
  {
   for( int i=l-1; i>=0; i-- )
    integrate();

   return *this;
  }

  template < class T >
  inline BPT& BPT::anormalize(void)
  {
   const lem::Math::REAL ai=abs( BaseArray<T>::back() );

   get_Container()[ size()-1 ] = T(1);

   for( int i=0; i<CastSizeToInt(size())-1; i++ )
    get_Container()[i] /= ai;

   return *this;
  }

  template < class T >
  inline BPT& BPT::operator+=( const BPT& b )
  {
   const int aord=Order();
   const int bord=b.Order();

   if( aord==bord )
    {
     for( int i=0; i<=aord; i++ )
      get_Container()[i] += b.get_Container()[i];
    }
   else
    {
     const int maxord = std::max( aord, bord );
     BPT res(maxord,NULL);

     for( int i=0; i<=maxord; i++ )
      res.get_Container()[i] = (i<=aord ? get_Container()[i]:T(0)) - (i<=bord ? b[i]:T(0));

     *this = res;
    }

   return *this;
  }


  template < class T >
  inline BPT& BPT::operator+=( const T a )
  {
   get_Container()[0] += a;
   return *this;
  }

  // -----------------------------------------------------------------
  // ����� ����� ��������, �������� ����� ����� � ���� �������������.
  // -----------------------------------------------------------------
  template < class T >
  inline BPT& BPT::operator-(void)
  {
   for( int i=Order(); i>=0; i-- )
    BaseArray<T>::get_Container()[i] = - BaseArray<T>::get_Container()[i];

   return *this;
  }

  template < class T >
  inline BPT& BPT::operator-=( const BPT& b )
  {
   const int aord=Order();
   const int bord=b.Order();

   if( aord==bord )
    {
     for( int i=0; i<=aord; i++ )
      BaseArray<T>::get_Container()[i] -= b[i];
    }
   else
    {
     const int maxord = std::max( aord, bord );
     BPT res(maxord,NULL);

     for( int i=0; i<=maxord; i++ )
      res.get_Container()[i] = (i<=aord ? BaseArray<T>::get_Container()[i] : T(0)) - (i<=bord ? b[i]:T(0));

     *this = res;
    }

   return *this;
  }

  template < class T >
  inline BPT& BPT::operator-=( const T a )
  {
   BaseArray<T>::operator[](0) -= a;
   return *this;
  }

  template < class T >
  inline BPT& BPT::operator*=( const BPT& b )
  {
   const int aord=Order();
   const int bord=b.Order();

   const int neword = aord+bord; // ������� ��������������� ��������.

   BPT res(neword,NULL);

   int i,j;
   lem::Math::REAL acoef;

   for( i=0; i<=aord; i++ )
    {
     acoef = BaseArray<T>::get_Container()[i];

     for( j=0; j<=bord; j++ )
      res.get_Container()[i+j] += acoef*b[j];
    }

   return (*this=res);
  }


  template < class T >
  inline BPT& BPT::operator*=( const T a )
  {
   for( int i=0; i<size(); i++ )
    BaseArray<T>::get_Container()[i] *= a;

   return *this;
  }


  template < class T >
  inline BPT& BPT::operator/=( const BPT& d )
  {
   BPT div,rem;

   divide( *this, d, div, rem );
   return (*this=div);
  }

  template < class T >
  inline BPT& BPT::operator/=( const T k )
  {
   for( int i=0; i<size(); i++ )
    BaseArray<T>::get_Container()[i] /= k;

   return *this;
  }

  template < class T >
  inline BPT& BPT::operator%=( const BPT& d )
  {
   BPT div, rem;

   divide( *this, d, div, rem );
   return (*this=rem);
  }

  // -------------------------------------------------------------
  // �������� ���� ���������. �������� �������, ������� ��������
  // ����� ����������� �� �������� ���������. ������� ���������
  // ����� �� ���������, � ���� ������ ����������� ������������
  // ����������� ������� ����.
  // This function performs polynomial addition, returns (a + b)
  // -------------------------------------------------------------
  template < class T >
  inline const BPT operator+( const BPT& a, const BPT& b )
  {
   const int aord=a.Order();
   const int bord=b.Order();

   const int maxord = std::max( aord, bord );
   BPT res(maxord,NULL);

   for( int i=0; i<=maxord; i++ )
    res[i] = (i<=aord ? a[i]:T(0)) + (i<=bord ? b[i]:T(0));

   return res;
  }

  template < class T >
  inline const BPT operator + ( const BPT& p, const T a )
  {
   BPT res=p;
   res[0] += a;
   return res;
  }

  template < class T >
  inline const BPT operator + ( const T a, const BPT& p )
  {
   BPT res=p;
   res[0] += a;
   return res;
  }



  template < class T >
  inline const BPT operator-( const BPT& a, const BPT& b )
  {
   const int aord=a.Order();
   const int bord=b.Order();

   const int maxord = std::max( aord, bord );

   BPT res(maxord,NULL);

   for( int i=0; i<=maxord; i++ )
    res[i] = (i<=aord ? a[i] : T(0)) - (i<=bord ? b[i] : T(0));

   return res;
  }


  template < class T >
  inline const BPT operator - ( const BPT& p, const T a )
  {
   BPT res=p;
   res[0] -= a;
   return res;
  }

  template < class T >
  inline const BPT operator - ( const T a, const BPT& p )
  {
   BPT res=p;
   res[0] -= a;
   return res;
  }


  // -------------------------------------------------------
  // �������� ������������ ���� ���������. � ����������
  // �������� �������, ������� �������� ����� ����� ��������
  // ����������.
  // -------------------------------------------------------
  template < class T >
  inline const BPT BPT::operator*( const BPT& b ) const
  {
   const int aord=Order();     // ������� ����������.
   const int bord=b.Order();

   const int neword = aord+bord; // ������� ��������������� ��������.

   BPT res(neword,NULL);   // ����� ����� ����������� ������������.

   int i,j;
   T acoef;

   for( i=0; i<=aord; i++ )
    {
     acoef = get(i);

     for( j=0; j<=bord; j++ )
      res[i+j] += acoef*b(j);
    }

   return res;
  }


  template < class T >
  inline const BPT BPT::operator*( const T a ) const
  {
   BPT res(*this);

   for( int i=0; i<size(); i++ )
    res[i] *= a;

   return res;
  }

  // --------------------------------------------------------------------------
  // ��� �������� ��������� ������� ������ � ��� ������, ���� ����� �� �������
  // � ��������� ������������ ��� ��������������� �����. ���� ���� �����
  // ������������� ��� ��������� ���������, � ������� ������������ �����
  // ��������� �����������, �������� �������� ��� ������������� ������.
  // ��� ����� ������� ���������� �������� ����������� ��������� ��������� �
  // �������������� ���������� '���������� ����������'.
  // --------------------------------------------------------------------------
  template < class T >
  inline bool operator==( BPT& a, BPT& b )
  {
   a.reduce();
   b.reduce();

   if( a.Order()!=b.Order() )
    return false;

   const int aord=a.Order();

   for( int i=0; i<=aord; i++ )
    if( a[i]!=b[i] )
     return false;

   return true;
  }

  template < class T >
  inline bool operator == ( BPT& a, const T b )
  {
   a.reduce();
   return a.Order()==0 && a[0]==b;
  }


  template < class T >
  inline bool operator!=( BPT& a, BPT& b )
  {
   a.reduce();
   b.reduce();

   if( a.Order()!=b.Order() )
    return true;

   const int aord=a.Order();

   for( int i=0; i<=aord; i++ )
    if( a[i]==b[i] )
     return false;

   return true;
  }

  template < class T >
  inline bool operator != ( BPT& a, const T b )
  {
   a.reduce();
   return a.Order()!=0 || a[0]!=b;
  }

  /**********************************************************************
   ���������� ������� �������� a �� ������� b, ������� ���������
   � div, ������� � rem.

   This function divides two polynomials and computes the remainder <rem>
   and <quotient>.
  ***********************************************************************/
  template < class T >
  inline void divide( const BPT &a, const BPT &b, BPT &div, BPT &rem )
  {
   const int aord=a.Order();
   const int bord=b.Order();

   BPT res(aord,NULL);
   BPT remainder(a);

   int i, x_order, rem_ord;
   T ck;

   while(true)
    {
     rem_ord = remainder.Order();
     x_order = rem_ord-bord;

     if( (rem_ord==0 && remainder[0]==T(0)) || x_order<0 )
      break;

     ck = remainder(rem_ord) / b(bord);

     res[x_order] = ck;

     for( i=0; i<=bord; i++ )
      remainder[rem_ord-i] -= b(bord-i)*ck;

     remainder.reduce();
    }

   div = res;
   rem = remainder;
   return;
  }


  template < class T >
  inline const BPT operator/( const BPT& p, const T k )
  {
   BPT res=p;

   for( int i=0; i<=p.Order(); i++ )
    res[i] /= k;

   return res;
  }

  template < class T >
  inline const BPT operator/( const T k, const BPT& p )
  {
   BPT res=p;

   if( !p.Order() )
    return buildpoly( k/res[0] );

   return BPT(0,NULL);
  }


  template < class T >
  inline const BPT operator%( const BPT& a, const BPT& b )
  {
   BPT div,rem;

   divide( a, b, div, rem );
   return rem;
  }

  // ---------------------------------------------------
  // �������� ������� �� ������ ��� ������. ��� �����
  // ������� ������������:
  //
  //        (x-r0)(x-r1)...(x-rn),
  // ��� ����� ri ���������� �����
  //
  // ---------------------------------------------------
  template < class T >
  inline const BPT build_by_roots( int N, const T *ri )
  {
   BPT result(0,NULL); result[0]=T(1);
   BPT p(1,NULL);      p[1] = T(1);

   for( int i=0; i<N; i++ )
    {
     p[0] = -ri[i];
     result *= p;
    }

   return result;
  }

  #if !defined LEM_NOREAL
  typedef BasePolynome<lem::Math::REAL> RPolynome;

  class OFormatter;
  extern void print( OFormatter& to, const RPolynome& x );
  #endif

  #undef BPT
 } // namespace 'lem'

#endif
