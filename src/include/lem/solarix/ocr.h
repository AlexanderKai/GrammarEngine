// CD->22.01.2007
// LC->06.03.2010
// --------------

#ifndef SOLARIX_OCR__H
#define SOLARIX_OCR__H
#pragma once

 #include <lem/ptr_container.h>
 #include <lem/qmatrix.h>
 #include <lem/zeroed.h>
 #include <lem/process.h>
 #include <lem/render/gdi.h>
 #include <lem/render/2d.h>
 #include <lem/math/random.h>
 #include <lem/xml_parser.h>
 #include <lem/math/histogram.h>

 //#define USE_FAST_EXP

 //#define NN_INTEGER

 namespace Solarix
 { 
  namespace Ocr
 {
  typedef float real;

  #if defined USE_FAST_EXP
  inline float Exp( float x )
  {
   const float xx=x*x;
   const float P = 12.F*xx+120.F;
   const float Q = x*(xx+60.F);
   return (P+Q)/(P-Q);
  }
  #else
   #define Exp(x) (exp(x))
  #endif


/* called fann_max, in order to not interferre with predefined versions of max */
#define fann_max(x, y) (((x) > (y)) ? (x) : (y))
#define fann_min(x, y) (((x) < (y)) ? (x) : (y))
#define fann_safe_free(x) {if(x) { free(x); x = NULL; }}
#define fann_clip(x, lo, hi) (((x) < (lo)) ? (lo) : (((x) > (hi)) ? (hi) : (x)))
/*#define fann_clip(x, lo, hi) (x)*/

#define fann_rand(min_value, max_value) (((float)(min_value))+(((float)(max_value)-((float)(min_value)))*rand()/(RAND_MAX+1.0f)))

#define fann_abs(value) (((value) > 0) ? (value) : -(value))

#ifdef FIXEDFANN

#define fann_mult(x,y) ((x*y) >> decimal_point)
#define fann_div(x,y) (((x) << decimal_point)/y)
#define fann_random_weight() (fann_type)(fann_rand(0,multiplier/10))
#define fann_random_bias_weight() (fann_type)(fann_rand((0-multiplier)/10,multiplier/10))

#else

#define fann_mult(x,y) (x*y)
#define fann_div(x,y) (x/y)
#define fann_random_weight() (fann_rand(-0.1f,0.1f))
#define fann_random_bias_weight() (fann_rand(-0.1f,0.1f))

#endif 



    /* Enum: activation_function_enum
       
	    The activation functions used for the neurons during training. The activation functions
	    can either be defined for a group of neurons by <neural_net::set_activation_function_hidden>
        and <neural_net::set_activation_function_output> or it can be defined for a single neuron by
        <neural_net::set_activation_function>.

	    The steepness of an activation function is defined in the same way by 
	    <neural_net::set_activation_steepness_hidden>, <neural_net::set_activation_steepness_output>
        and <neural_net::set_activation_steepness>.
       
       The functions are described with functions where:
       * x is the input to the activation function,
       * y is the output,
       * s is the steepness and
       * d is the derivation.

       FANN_LINEAR - Linear activation function. 
         * span: -inf < y < inf
	     * y = x*s, d = 1*s
	     * Can NOT be used in fixed point.

       FANN_THRESHOLD - Threshold activation function.
	     * x < 0 -> y = 0, x >= 0 -> y = 1
	     * Can NOT be used during training.

       FANN_THRESHOLD_SYMMETRIC - Threshold activation function.
	     * x < 0 -> y = 0, x >= 0 -> y = 1
	     * Can NOT be used during training.

       FANN_SIGMOID - Sigmoid activation function.
	     * One of the most used activation functions.
	     * span: 0 < y < 1
	     * y = 1/(1 + exp(-2*s*x))
	     * d = 2*s*y*(1 - y)

       FANN_SIGMOID_STEPWISE - Stepwise linear approximation to sigmoid.
	     * Faster than sigmoid but a bit less precise.

       FANN_SIGMOID_SYMMETRIC - Symmetric sigmoid activation function, aka. tanh.
	     * One of the most used activation functions.
	     * span: -1 < y < 1
	     * y = tanh(s*x) = 2/(1 + exp(-2*s*x)) - 1
	     * d = s*(1-(y*y))

       FANN_SIGMOID_SYMMETRIC - Stepwise linear approximation to symmetric sigmoid.
	     * Faster than symmetric sigmoid but a bit less precise.

       FANN_GAUSSIAN - Gaussian activation function.
	     * 0 when x = -inf, 1 when x = 0 and 0 when x = inf
	     * span: 0 < y < 1
	     * y = exp(-x*s*x*s)
	     * d = -2*x*s*y*s

       FANN_GAUSSIAN_SYMMETRIC - Symmetric gaussian activation function.
	     * -1 when x = -inf, 1 when x = 0 and 0 when x = inf
	     * span: -1 < y < 1
	     * y = exp(-x*s*x*s)*2-1
	     * d = -2*x*s*(y+1)*s
    	 
       FANN_ELLIOT - Fast (sigmoid like) activation function defined by David Elliott
	     * span: 0 < y < 1
	     * y = ((x*s) / 2) / (1 + |x*s|) + 0.5
	     * d = s*1/(2*(1+|x*s|)*(1+|x*s|))
    	 
       FANN_ELLIOT_SYMMETRIC - Fast (symmetric sigmoid like) activation function defined by David Elliott
	     * span: -1 < y < 1   
	     * y = (x*s) / (1 + |x*s|)
	     * d = s*1/((1+|x*s|)*(1+|x*s|))

	    FANN_LINEAR_PIECE - Bounded linear activation function.
	     * span: 0 < y < 1
	     * y = x*s, d = 1*s
    	 
	    FANN_LINEAR_PIECE_SYMMETRIC - Bounded Linear activation function.
	     * span: -1 < y < 1
	     * y = x*s, d = 1*s
	
        FANN_SIN_SYMMETRIC - Periodical sinus activation function.
         * span: -1 <= y <= 1
         * y = sin(x*s)
         * d = s*cos(x*s)
         
        FANN_COS_SYMMETRIC - Periodical cosinus activation function.
         * span: -1 <= y <= 1
         * y = cos(x*s)
         * d = s*-sin(x*s)
    	 
	    See also:
		    <neural_net::set_activation_function_hidden>,
		    <neural_net::set_activation_function_output>
    */
    enum activation_function_enum {
        FANN_LINEAR,
        FANN_THRESHOLD,
        FANN_THRESHOLD_SYMMETRIC,
        FANN_SIGMOID,
        FANN_SIGMOID_STEPWISE,
        FANN_SIGMOID_SYMMETRIC,
        FANN_SIGMOID_SYMMETRIC_STEPWISE,
        FANN_GAUSSIAN,
        FANN_GAUSSIAN_SYMMETRIC,
        FANN_GAUSSIAN_STEPWISE,
        FANN_ELLIOT,
        FANN_ELLIOT_SYMMETRIC,
        FANN_LINEAR_PIECE,
        FANN_LINEAR_PIECE_SYMMETRIC,
	    FANN_SIN_SYMMETRIC,
	    FANN_COS_SYMMETRIC
    };



 /* Implementation of the activation functions */

 /* stepwise linear functions used for some of the activation functions */

 /* defines used for the stepwise linear functions */

 #define fann_linear_func(v1, r1, v2, r2, sum) (((((r2)-(r1)) * ((sum)-(v1)))/((v2)-(v1))) + (r1))
 #define fann_stepwise(v1, v2, v3, v4, v5, v6, r1, r2, r3, r4, r5, r6, min, max, sum) (sum < v5 ? (sum < v3 ? (sum < v2 ? (sum < v1 ? min : fann_linear_func(v1, r1, v2, r2, sum)) : fann_linear_func(v2, r2, v3, r3, sum)) : (sum < v4 ? fann_linear_func(v3, r3, v4, r4, sum) : fann_linear_func(v4, r4, v5, r5, sum))) : (sum < v6 ? fann_linear_func(v5, r5, v6, r6, sum) : max))

 /* FANN_LINEAR */
 /* #define fann_linear(steepness, sum) fann_mult(steepness, sum) */
 #define fann_linear_derive(steepness, value) (steepness)

 /* FANN_SIGMOID */
 #define fann_sigmoid(steepness, sum) (1.0f/(1.0f + exp(-2.0f * steepness * sum)))
 #define fann_sigmoid_real(sum) (1.0f/(1.0f + exp(-2.0f * sum)))
 #define fann_sigmoid_derive(steepness, value) (2.0f * steepness * value * (1.0f - value))

 /* FANN_SIGMOID_SYMMETRIC */
 #define fann_sigmoid_symmetric(steepness, sum) (2.0f/(1.0f + exp(-2.0f * steepness * sum)) - 1.0f)
 #define fann_sigmoid_symmetric_real(sum) (2.0f/(1.0f + exp(-2.0f * sum)) - 1.0f)
 #define fann_sigmoid_symmetric_derive(steepness, value) steepness * (1.0f - (value*value))

 /* FANN_GAUSSIAN */
 #define fann_gaussian(steepness, sum) (exp(-sum * steepness * sum * steepness))
 #define fann_gaussian_real(sum) (exp(-sum * sum))
 #define fann_gaussian_derive(steepness, value, sum) (-2.0f * sum * value * steepness * steepness)

 /* FANN_GAUSSIAN_SYMMETRIC */
 /* #define fann_gaussian_symmetric(steepness, sum) ((exp(-sum * steepness * sum * steepness)*2.0)-1.0) */
 #define fann_gaussian_symmetric_real(sum) ((exp(-sum * sum)*2.0f)-1.0f)
 #define fann_gaussian_symmetric_derive(steepness, value, sum) (-2.0f * sum * (value+1.0f) * steepness * steepness)

 /* FANN_ELLIOT */
 /* #define fann_elliot(steepness, sum) (((sum * steepness) / 2.0f) / (1.0f + fann_abs(sum * steepness)) + 0.5f) */
 #define fann_elliot_real(sum) (((sum) / 2.0f) / (1.0f + fann_abs(sum)) + 0.5f)
 #define fann_elliot_derive(steepness, value, sum) (steepness * 1.0f / (2.0f * (1.0f + fann_abs(sum)) * (1.0f + fann_abs(sum))))

 /* FANN_ELLIOT_SYMMETRIC */
 /* #define fann_elliot_symmetric(steepness, sum) ((sum * steepness) / (1.0f + fann_abs(sum * steepness)))*/
 #define fann_elliot_symmetric_real(sum) ((sum) / (1.0f + fann_abs(sum)))
 #define fann_elliot_symmetric_derive(steepness, value, sum) (steepness * 1.0f / ((1.0f + fann_abs(sum)) * (1.0f + fann_abs(sum))))

 /* FANN_SIN_SYMMETRIC */
 #define fann_sin_symmetric_real(sum) (sin(sum))
 #define fann_sin_symmetric_derive(steepness, sum) (steepness*cos(steepness*sum))

 /* FANN_COS_SYMMETRIC */
 #define fann_cos_symmetric_real(sum) (cos(sum))
 #define fann_cos_symmetric_derive(steepness, sum) (steepness*-sin(steepness*sum))

 /* FANN_SIN */
 #define fann_sin_real(sum) (sin(sum)/2.0f+0.5f)
 #define fann_sin_derive(steepness, sum) (steepness*cos(steepness*sum)/2.0f)

 /* FANN_COS */
 #define fann_cos_real(sum) (cos(sum)/2.0f+0.5f)
 #define fann_cos_derive(steepness, sum) (steepness*-sin(steepness*sum)/2.0f)

 #define fann_activation_switch(activation_function, value, result) \
 switch(activation_function) \
 { \
	case FANN_LINEAR: \
		result = (fann_type)value; \
        break; \
	case FANN_LINEAR_PIECE: \
		result = (fann_type)((value < 0) ? 0 : (value > 1) ? 1 : value); \
        break; \
	case FANN_LINEAR_PIECE_SYMMETRIC: \
		result = (fann_type)((value < -1) ? -1 : (value > 1) ? 1 : value); \
        break; \
	case FANN_SIGMOID: \
		result = (fann_type)fann_sigmoid_real(value); \
        break; \
	case FANN_SIGMOID_SYMMETRIC: \
		result = (fann_type)fann_sigmoid_symmetric_real(value); \
        break; \
	case FANN_SIGMOID_SYMMETRIC_STEPWISE: \
		result = (fann_type)fann_stepwise(-2.64665293693542480469e+00, -1.47221934795379638672e+00, -5.49306154251098632812e-01, 5.49306154251098632812e-01, 1.47221934795379638672e+00, 2.64665293693542480469e+00, -9.90000009536743164062e-01, -8.99999976158142089844e-01, -5.00000000000000000000e-01, 5.00000000000000000000e-01, 8.99999976158142089844e-01, 9.90000009536743164062e-01, -1, 1, value); \
        break; \
	case FANN_SIGMOID_STEPWISE: \
		result = (fann_type)fann_stepwise(-2.64665246009826660156e+00, -1.47221946716308593750e+00, -5.49306154251098632812e-01, 5.49306154251098632812e-01, 1.47221934795379638672e+00, 2.64665293693542480469e+00, 4.99999988824129104614e-03, 5.00000007450580596924e-02, 2.50000000000000000000e-01, 7.50000000000000000000e-01, 9.49999988079071044922e-01, 9.95000004768371582031e-01, 0, 1, value); \
        break; \
	case FANN_THRESHOLD: \
		result = (fann_type)((value < 0) ? 0 : 1); \
        break; \
	case FANN_THRESHOLD_SYMMETRIC: \
		result = (fann_type)((value < 0) ? -1 : 1); \
        break; \
	case FANN_GAUSSIAN: \
		result = (fann_type)fann_gaussian_real(value); \
        break; \
	case FANN_GAUSSIAN_SYMMETRIC: \
		result = (fann_type)fann_gaussian_symmetric_real(value); \
        break; \
	case FANN_ELLIOT: \
		result = (fann_type)fann_elliot_real(value); \
	    break; \
	case FANN_ELLIOT_SYMMETRIC: \
		result = (fann_type)fann_elliot_symmetric_real(value); \
        break; \
	case FANN_SIN_SYMMETRIC: \
		result = (fann_type)fann_sin_symmetric_real(value); \
        break; \
	case FANN_COS_SYMMETRIC: \
		result = (fann_type)fann_cos_symmetric_real(value); \
        break; \
	case FANN_SIN: \
		result = (fann_type)fann_sin_real(value); \
        break; \
	case FANN_COS: \
		result = (fann_type)fann_cos_real(value); \
        break; \
	case FANN_GAUSSIAN_STEPWISE: \
        result = 0; \
        break; \
}

 struct RecognitionOptions
 {
  lem::zbool apply_mask; // ��������� ���������� ����������� �����
  real mask_factor; // ������� ������� ����� ��������: 0 - �� ������ (���������� apply_mask=false),
                        //                                 1 - ��������� ������
 };


 // **************************
 // ������� ���� ��������.
 // **************************
 class InputSignals
 {
  protected:
   int size; // ����������� ������� ��������

  public: 
   InputSignals( int _size );
   virtual ~InputSignals(void) {}

   virtual real Get( int i ) const=0;
   virtual void Nullify(void)=0;

   inline int Size(void) const { return size; }

   virtual void Print( lem::OFormatter &out ) const=0;

   virtual bool CanBeShifted(void) const { return false; }
   virtual void GenerateShifted( lem::MCollect<InputSignals*> &generated ) const {}

   virtual void GenerateNoised( lem::MCollect<InputSignals*> &generated ) const {}
 };


 // ********************************
 // ���������� ��� ������� ��������
 // ********************************
 class InputVector : public InputSignals
 {
  public:
   lem::MCollect<real> in;

  public: 
   InputVector( int size );
   virtual real Get( int i ) const;
   virtual void Nullify(void);

   virtual void Print( lem::OFormatter &out ) const;
 };


 // ****************************************
 // ���������� ��� ����������� ���� ��������
 // ****************************************
 class InputBitmap : public InputSignals
 {
  public:
   lem::FMatrix m; // �������� �������
   int w,h;

   bool scale_if_smaller; 
   int offset_x, offset_y;
   lem::Path bg_file; // ���� � �����������, �� ������� ������������� �������

   lem::zbool center_if_smaller; // ���� ����������� ����������� ������,
                                 // ��� ���� ����, �� ������ ������������
                                 // �������� �� ���� � ��������� �������
                                 // ����� �����.

  public: 
   InputBitmap( int W, int H );

   // ��������� �������� �� ���������� ����� � ��������������
   // ������� �������� ���������� �������.
   bool Load( const lem::Path &bmp_filename ); 

   virtual void Nullify(void);

   // �������� ������� � ������� ���������� ���� ������
   virtual real Get( int i ) const;

   virtual void Print( lem::OFormatter &out ) const;

   virtual bool CanBeShifted(void) const { return true; }
   virtual void GenerateShifted( lem::MCollect<InputSignals*> &generated ) const;
   virtual void GenerateNoised( lem::MCollect<InputSignals*> &generated ) const;

   void ApplyMask( const lem::FMatrix &mask, const RecognitionOptions &params );
 };

 class Pattern;
 typedef lem::Ptr_NC_Collect<Pattern> Patterns;


 class Pattern
 {
  public:
   int id; // ���������� id �������
   lem::Path image_filename; // �� ������ ����� �������� �����
   lem::Ptr<InputSignals> in;
   lem::MCollect<real> out; // ����� ������ ���� ���������
   int n_input;

   lem::zbool store_cache; // ��� sliding ������ - ��������� ��� ������
   lem::MCollect<real> cached_ain; // �������������� ������� �� ������� ����������,
                                     // ��� ��������� ���������� ��������� ��������� ���������
   
   enum OutLogic { SingleSignal, OrSignals, AndSignals, FullVector };
   OutLogic outlogic; // �������������� �������� �������� ��������

   int ideal_output; // ����� �� ������ ������ ���� ������ 1 ������
   lem::zbool any_signal; // �������� ����� �������� ������ - �������� �� �����������

   lem::zbool is_positive; // ���� ������� ���� ���������� ������
 
  public:
   Pattern(void);
   Pattern( const Pattern& x ); 
   Pattern( lem::Ptr<InputSignals> input, int n_output, int isignal=UNKNOWN );
   Pattern(
           lem::Ptr<InputSignals> input,
           int n_output,
           OutLogic logic,
           lem::MCollect<int> & isignal
          );

   virtual ~Pattern() {}

   real GetInData( int i ) const;
   inline real GetOutData( int i ) const { return out[i]; }
   
   void MatchIdeal( int isignal ) const;

   void PrintIdeal( lem::OFormatter &out ) const;

   virtual void GenerateShiftedPatterns( Patterns &store ) const;
   virtual void GenerateNoisedPatterns( Patterns &store ) const;

   void ApplyMask( const lem::FMatrix &mask, const RecognitionOptions &params );

   inline bool IsPositive(void) const { return is_positive; }
 };

 class AnyPattern : public Pattern
 {
  public:
   AnyPattern( lem::Ptr<InputSignals> input );
 };

 class PatternInline : public Pattern
 {
  public:
   PatternInline( const real *in, int nin, const real *out, int nout );
 };

 class LoopbackPattern : public Pattern
 {
  public:
   LoopbackPattern( lem::Ptr<InputSignals> input );
 };



 class AGaussianRandU : public lem::Math::GaussianRandU
 {
  public:
   AGaussianRandU(void):lem::Math::GaussianRandU() {}
   AGaussianRandU( const real M, const real Sigma, const int N=6 )
   : lem::Math::GaussianRandU(M,Sigma,N){}

   inline const real aget(void)
   {
    #if defined LEM_MSC && _MSC_VER<1300
    return (real)lem::Math::qabs( ((lem::Math::GaussianRandU&)*this).aget()/2. );
    #else
    return (real)lem::Math::qabs(lem::Math::GaussianRandU::aget()/2.);
    #endif
   }
 };

 class NeuroNet;

 // ��� ������������� �������
 enum { NN_LINEAR_CELL, NN_LOGISTIC_CELL, NN_TANH_CELL, NN_LOGISTIC2_CELL };

 #if defined NN_INTEGER
 typedef int LinkType;
 #else
 typedef real LinkType;
 #endif

 // ������������ ������ ���� - ��������� ��������.
 struct Neuron
 {
  int id; // ���������� ��� ������� ��� ��� �������� ������ ��� �������� �� ��������� �����

  lem::MCollect<Neuron*> in;  // ��������� �� �����.
  lem::MCollect<LinkType> w_in;   // ���� ������.

  lem::MCollect<Neuron*> out; // ��������� �� ������.
  lem::MCollect<LinkType> w_out;  // ���� ������.

  #if defined OCR_SUPPORT_ACTIVATION_FUNCTIONS
  int yieldfun;               // ���������� ��� ���������
  #endif

  LinkType A;                 // ������� ����������.
  LinkType T;                 // ����� ������������ (threshold).
  //int Asign;

  LinkType dE_dy,dE_ds,ThreshError;

  real EPSILON;
  
  LinkType sum_error;
  bool enabled;

  lem::MCollect<LinkType> WeightError;

  Neuron( int Id=UNKNOWN );

  Neuron( const Neuron &x );
  void operator=( const Neuron &x );
  void Init( const Neuron &x );

  inline void FixA( const LinkType a )
  {
   A=a;
   return;
  }

  bool AttachSupplier( Neuron *supplier, LinkType W );
  bool AttachReceiver( Neuron *receiver, LinkType W );

  void Crunch(void);

  inline real CalcDerive( real x ) const
  {
   #if defined OCR_SUPPORT_ACTIVATION_FUNCTIONS
   return yieldfun==NN_LOGISTIC_CELL ? x*(1.0F-x) : 1.0F-x*x;
/*
   switch(yieldfun)
   {
    case NN_LOGISTIC_CELL:  return x*(1.0-x); //fann_sigmoid_derive( steepness, x );
    case NN_TANH_CELL:      return 1.0-x*x; //fann_sigmoid_symmetric_derive( steepness, x ); 
    case NN_LOGISTIC2_CELL: return x*(1.0-x);
    default: LEM_STOPIT;
   }
*/
   #else
   return x*(1.0F-x);
   #endif
  }

  bool IsAttachedTo( const Neuron &x ) const;

  void SaveBin( lem::Stream &bin ) const;
  void LoadBin( lem::Stream &bin, const NeuroNet &net );

  void AssembleLinksInfo( lem::Histogramma &h ) const;

  void ForgetReceiver( const Neuron *n );

  void ForgetAllReceivers(void);

  void TrainingBegins(void) { sum_error=0; }

  void AddLinksNoise( real factor );
  void Reattach( const Neuron *old_ptr, Neuron *new_ptr );

 };


 class NeuronVisitor
 {
  public:
   NeuronVisitor(void) {}
   virtual ~NeuronVisitor(void) {}
   virtual bool operator()( Neuron &x ) { return operator()( (const Neuron&)x ); }
   virtual bool operator()( const Neuron &x )=0;
 };


 class NeuroNet;
 class Alceptor;



 #if defined NN_INTEGER
 const int DENORM=100;
 const int DENORM2 = DENORM*DENORM;
 const int DENORM3 = DENORM2*DENORM;
 extern LinkType E_FUN[];
 inline LinkType iFun( LinkType x )
 {
  return x>=0 && x<=1000 ? E_FUN[x+500] : ( x>=1000 ? E_FUN[999] : E_FUN[0] );
 }
 #endif


 struct NetLayerGeometry : lem::NonCopyable
 {
  lem::MCollect<int> n_items; // ������� �����
 };



 class NeuroNet
 {
  public:
   int nlayer;    // ����� ����� ����.
   lem::MCollect<int> nitem;     // ����� ��������� � ������ ����.
   int n_in; // ������� �������� ��������� �� ����
   int n_out; // ������� �������� �������� �� ������

   lem::zbool has_alceptors;

  protected:
   Neuron **net; // ������������� ������� �� ���������.
   lem::MCollect<real> layer_eps; // ������������ ����������� �����, �� ��������� = 1.

   lem::MCollect<Neuron*> in;  // ��������� �� �����.
   lem::MCollect<Neuron*> out; // ��������� �� ������.

   void AttachInputs(void);
   void AttachOutputs(void);
   void AttachLayers( real Locality );

   virtual void FixInput( Pattern &In );
   virtual void ForwardPropagation(void);
   virtual void BackwardPropagation( const Pattern &Goal );
   virtual void UpDateWeightAndThresh(void);
   virtual real CalcDerivs( const Pattern &Goal );

   void Delete(void);
   void Init( const NeuroNet & x );

   void Build( const NetLayerGeometry &geom, real Locality );

   #if defined NN_INTEGER
   int EPSILON;
   #else
   real EPSILON;
   #endif

  public:
   lem::CloneCollect<Alceptor> alceptors;

  public:
   NeuroNet(void);
   NeuroNet( int nLayer, int nItems, int nIn, int nOut, real LayerOversize, real Locality );
   NeuroNet( const NetLayerGeometry &geom, real Locality );
   NeuroNet( lem::Stream &bin );

   NeuroNet( const NeuroNet & x );
   void operator=( const NeuroNet & x );

   virtual ~NeuroNet(void);

   #if defined OCR_SUPPORT_ACTIVATION_FUNCTIONS
   void SetActivationFunctions( bool linear, bool logistic, bool tanh_fun, bool logistic2 );
   #endif


   void SetEpsilon( real e );
   real GetEpsilon(void) const;

   virtual int CountNodes(void) const;
   int CountOutput(void) const { return n_out; }
   virtual int CountAlceptors(void) const;
   virtual int CountLinks(void) const;

   #if defined NN_INTEGER
   real GetOutput( int i ) const { return real(out[i]->A)/DENORM; }
   #else
   real GetOutput( int i ) const { return out[i]->A; }
   #endif

   virtual real LearnIt( Pattern &pattern );

   virtual void Recognize( Pattern &pattern );
   virtual std::pair<int,real> GetYieldSignal(void) const;

   virtual const Neuron & GetNeuron( int layer, int pos ) const
   {
    LEM_CHECKIT_Z( layer<nlayer );
    LEM_CHECKIT_Z( pos<nitem[layer] );
    return net[layer][pos];
   }

   virtual Neuron & GetNeuron( int layer, int pos )
   {
    LEM_CHECKIT_Z( layer<nlayer );
    LEM_CHECKIT_Z( pos<nitem[layer] );
    return net[layer][pos];
   }

   real TestPattern( Pattern &pattern, bool &hit );

   virtual void PrintOutput( lem::OFormatter &out ) const;

   virtual void SaveBin( lem::Stream &bin ) const;
   virtual void LoadBin( lem::Stream &bin );

   virtual Neuron* FindNeuronById( int id ) const;

   virtual void AssembleLinksInfo( lem::Histogramma &h ) const;

   virtual void VisitNeurons( NeuronVisitor &visitor );
   virtual void VisitNeurons( NeuronVisitor &visitor ) const;

   real CalcAlceptorValue( int ialceptor ) const;
   real CalcNeuronValue( const Neuron &n ) const;

   void SetLayerEpsilon( int layer_index, real e );
   void SetNeuronsEpsilon( int layer_index, real e );
   void AddLayer( int after_layer_index );
   void AddNeurons( int layer_index, real factor );
   void AddNoise( real factor );
   void AddLinks(void);
   void RemoveLayer( int layer_index );
 };


 class LetterRecognizer; 

 class Alceptor : public NeuroNet
 {
  public:
   real sum_delta;
   lem::UFString class_name; // ��� ������ ��� ���������
   lem::UFString name; // �������� ���, human readable, ���������� ��� ������� ���������
 
   static Alceptor* load( lem::Stream &bin );

  protected:
   int x0, y0;
   int ioffset; // �������� ��� ���������� ������� ������� � ������������ ������� �������
   int outer_raster_w, outer_raster_h;

   void Init( const Alceptor &x );

  public:
   Alceptor( int iOffset, int X0, int Y0, int _outer_raster_w, int _outer_raster_h );
   Alceptor(void);
   Alceptor( const Alceptor &x );
   virtual ~Alceptor(void);

   void operator=( const Alceptor &x );

   virtual Alceptor* Optimize(void);

   //virtual void FixInput( Pattern &pattern );
   virtual void StoreOutput( lem::MCollect<real> &out ) const;

   virtual void SaveBin( lem::Stream &bin ) const;
   virtual void LoadBin( lem::Stream &bin );
   void LoadBinFromNet( lem::Stream &bin );

   virtual void InitFromNet( const NeuroNet &n );

   // ���������� ������� ������, �� ������� �������� ������ ���������� ����� ������.
   virtual std::pair<int,int> GetOutputSignalsRange(void) const;

   virtual Alceptor* clone(void) const;
 };


 class AlgoAlceptor : public Alceptor
 {
  protected:
   int field_w, field_h; // ������� ���� ��������, �� ������� ����������� ������
   real field_size; // ����� ���-�� �������� � ����
   lem::MCollect<real> out_res; // ��������� ������

  public:
   AlgoAlceptor( int iOffset, int X0, int Y0, int W, int H, int _outer_raster_w, int _outer_raster_h );
   AlgoAlceptor(void);
   AlgoAlceptor( const AlgoAlceptor &x );

   virtual void FixInput( Pattern &pattern );
   virtual void StoreOutput( lem::MCollect<real> &out ) const;

   virtual void SaveBin( lem::Stream &bin ) const;
   virtual void LoadBin( lem::Stream &bin );

   virtual Alceptor* clone(void) const;
 };



 // �������������� �������� - ������ �� ���� �������� �������� ���������������,
 // ��������� � �.�.
 class StatsAlceptor : public AlgoAlceptor
 {
  public:
   StatsAlceptor( int iOffset, int X0, int Y0, int W, int H, int _outer_raster_w, int _outer_raster_h );
   StatsAlceptor( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };


 // ����������� ������� ������ - �������� ������ �������� ������ ������ �������
 // �� ���� ����. ��� ���������� ��� ���������� ���������� ����, �������
 // ������ � �� �������� ��������, � �� ������� ����������.
 class PixelAlceptor : public AlgoAlceptor
 {
  private:
   real factor;

  public:
   PixelAlceptor( int iOffset, int X0, int Y0, int _outer_raster_w, int _outer_raster_h, real _factor );
   PixelAlceptor( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual void SaveBin( lem::Stream &bin ) const;
   virtual void LoadBin( lem::Stream &bin );
   virtual Alceptor* clone(void) const;
 };


 class Prime1Alceptor : public AlgoAlceptor
 {
  public:
   Prime1Alceptor( int iOffset, int X0, int Y0, int W, int H, int _outer_raster_w, int _outer_raster_h );
   Prime1Alceptor( lem::Stream &bin );
   Prime1Alceptor( const Prime1Alceptor &x );

   virtual void FixInput( Pattern &pattern );

   virtual Alceptor* Optimize(void);
   virtual Alceptor* clone(void) const;
 };

 class Prime2x2Alceptor : public Prime1Alceptor
 {
  public:
   Prime2x2Alceptor( int iOffset, int X0, int Y0, int _outer_raster_w, int _outer_raster_h );
   Prime2x2Alceptor( lem::Stream &bin );
   Prime2x2Alceptor( const Prime1Alceptor &x );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };

 class Prime3x3Alceptor : public Prime1Alceptor
 {
  public:
   Prime3x3Alceptor( int iOffset, int X0, int Y0, int _outer_raster_w, int _outer_raster_h );
   Prime3x3Alceptor( lem::Stream &bin );
   Prime3x3Alceptor( const Prime1Alceptor &x );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };


 class Prime2Alceptor : public AlgoAlceptor
 {
  public:
   Prime2Alceptor( int iOffset, int X0, int Y0, int W, int H, int _outer_raster_w, int _outer_raster_h );
   Prime2Alceptor( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };

 class DirectionAlceptor : public AlgoAlceptor
 {
  public:
   DirectionAlceptor( int iOffset, int X0, int Y0, int W, int H, int _outer_raster_w, int _outer_raster_h );
   DirectionAlceptor( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };


 // ***************************************************************
 // ����������� �������� ��� �������� ���������� - ������ �� ����
 // ���� ������ ���� � �� �� ��������.
 // ***************************************************************
 class ConstAlceptor : public AlgoAlceptor
 {
  private:
   real yield;

  public:
   ConstAlceptor( int iOffset, real yield );
   ConstAlceptor( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual void SaveBin( lem::Stream &bin ) const;
   virtual void LoadBin( lem::Stream &bin );
   virtual Alceptor* clone(void) const;
 };





 struct SlidingSession : lem::NonCopyable
 {
  lem::Path filename; // �������� ���� ��������

  // �������� ����������� ��������
  lem::Ptr<lem::Render::Image> image;

  // �������� � ���� ������� ������������ �����
  lem::Ptr<lem::FMatrix> matrix;

  // ��������� "����������" ������� ��� ���������� ��������
  lem::PtrCollect< Pattern > signals;
 };

 struct IncorrectRecognition : lem::NonCopyable
 {
  bool is_test_pattern; // ������� �� ��������� test
  int isession; // ����� ��������
  int islide; // � ������ ��� sliding sesssions
  lem::Path pattern_filename; // ��� ����� � ���������
  const Pattern *pattern; // ��� ������� - ��������� �� ������������� �������
  real error; // �������� ������
  lem::MCollect<real> out; // ������� �� ������ ��������

  IncorrectRecognition(void);
 };
  

 struct CharSignal : lem::NonCopyable
 {
  lem::MCollect<wchar_t> chars; // �������������� �����������

  bool Match( wchar_t c ) const { return chars.find(c)!=UNKNOWN; }

  void SaveBin( lem::Stream &bin ) const;
  void LoadBin( lem::Stream &bin );
 };

 // *************************************************************
 // �������� ��������� ������� - �������� (human-readable) ���,
 // *************************************************************
 struct Signal
 {
  lem::zbool is_not;
  lem::UFString name, external_name;
  lem::Collect< lem::UFString > name_items, external_name_items; // ��� N����� - ��������� �������

  Signal(void) {}
  Signal( const Signal &x );

  void ParseNGram(void);

  void operator=( const Signal &x );

  inline bool operator==( const Signal &x ) const { return name==x.name; }
  inline bool operator!=( const Signal &x ) const { return name!=x.name; }

  void SaveBin( lem::Stream &bin ) const;
  void LoadBin( lem::Stream &bin );

  inline bool IsNot(void) const{ return is_not; }
  inline bool IsPositive(void) const{ return !is_not; }

  const lem::UFString& GetBestName(void) const;
 }; 





class NeuronLinksCounter : public NeuronVisitor
{
 public:
  int count;

 public:
  NeuronLinksCounter(void) { count=0; }
  virtual bool operator()( const Neuron &x )
  {
   count += (int)x.w_in.size();
   return true;
  }

  //virtual bool operator()( Neuron &x ) { return false; }
};


  struct Feature;


/*
  struct PredicateVar
  {
   lem::zbool unified; // ���������� ��������� ��������
   lem::FString value;
  };
*/


  enum PredicateNames {
             i_LINE,
             i_ARC,
             i_CIRCLE,
             #if defined T_DETECTORS
             i_T,
             #endif
             #if defined X_DETECTORS
             i_X, 
             #endif
             #if defined V_DETECTORS
             i_V, 
             #endif 
             i_JOIN,
             i_INTERSECT,
             i_PARALLEL,
             i_ORTHOGONAL,
             i_LEFT_RIGHT,
             i_UP_DOWN,
             i_UP_HALF,
             i_DOWN_HALF,
             i_LEFT_HALF,
             i_RIGHT_HALF,
             i_HORIZONTAL,
             i_VERTICAL,
             i_RSLOP,
             i_LSLOP,
             i_LEFT,
             i_RIGHT,
             i_UP,
             i_DOWN,
             i_SAME_CENTER_X,
             i_SAME_CENTER_Y
};




  // ***********************************************************
  // ����� ����� Features ��� �������� ����� ���������� Feature
  // ***********************************************************
  struct Predicate
  {
   int iname;
   lem::MCollect<const Feature*> args;

   int weight; // ��� - ����� ����� ������������ ���������� ���
   real rel; // ������������� ���������
 
   Predicate( int Name );
   Predicate( int Name, const Feature *x1 );
   Predicate( int Name, const Feature *x1, const Feature *x2 );
   Predicate( const Predicate &x );

   void operator=( const Predicate &x );

   bool operator==( const Predicate &x );
   bool operator!=( const Predicate &x );

   static void Build( const Feature &a, const Feature &b, int MaxFeatureSize, lem::MCollect<Predicate*> &res );

   int Arity(void) const { return CastSizeToInt(args.size()); }

   void Print( lem::OFormatter &to ) const;

/*
   bool Unify( int head ) const;
   bool Unify( int Head, PredicateVar &arg0 ) const;
   bool Unify( int Head, PredicateVar &arg0, PredicateVar &arg1 ) const;
   bool Unify( int Head, PredicateVar &arg0, PredicateVar &arg1, PredicateVar &arg2 ) const;
*/

   static const char* IntToName( int iname );

   static bool FindPredicate( 
                             const lem::MCollect<Predicate*> &res,
                             int iName, 
                             const Feature &_1,
                             const Feature &_2
                            );

   real GetRel(void) const { return rel; }
   int GetWeight(void) const { return weight; }
  };


  struct PredicateTemplate
  {
   int iname;
   real rel;
   lem::MCollect<int> args;

   PredicateTemplate(void);
   PredicateTemplate( const PredicateTemplate &x );
   PredicateTemplate( const Predicate &x, const lem::MCollect<const void*> &arg_subst );

   void operator=( const PredicateTemplate &x );

   bool operator==( const PredicateTemplate &x ) const;
   bool operator!=( const PredicateTemplate &x ) const;

   int Arity(void) const { return CastSizeToInt(args.size()); }

   void Print( lem::OFormatter &to ) const;

   bool UnifyWith( const PredicateTemplate &x, const lem::MCollect<int>& vars_map ) const;

   void SaveBin( lem::Stream &file ) const;
   void LoadBin( lem::Stream &file );
  };


  class FeatureDetector;
  class FeaturesMapping;

  // ************************************************
  // ��������� � ����������� �������������� ��������
  // ************************************************
  struct Feature : public boost::noncopyable
  {
   int id;
   const FeatureDetector *detector; // ����� �������� ��������
   real rel; // �������������
   lem::PtrCollect<Predicate> predicates;
   lem::MCollect<lem::Render::Point2di> hit_points;

   lem::zbool reduced; // ������ true, ���� ������ �������� ������� ��� � ���
                       // ������� ����� ���������� �� �������� �������.

   int length; // ������������ �������������, ��� ����� - �����

   lem::zbool is_line;
   real angle;  // ���� ������� ������ �����
   lem::Render::Point2di pbeg, pend; // ����� �������

   lem::Render::Point2di center; // "����� �������"
   int Xmin, Xmax, Ymin, Ymax; // ������������ �������������
   
   Feature(void);

   void CommitGeometryCalculations( FeaturesMapping &mapping );
   bool RestoreMissingPixels( FeaturesMapping &mapping );

   void Print( lem::OFormatter &to ) const;
   void AddPredicates1( const lem::PtrCollect<Predicate> &list, int weight );
   void AddPredicate( Predicate *p );

   static float Distance( const lem::MCollect<lem::Render::Point2di> &data1,
                          const lem::MCollect<lem::Render::Point2di> &data2 );


   static float Distance( const Feature &a, const Feature &b );

   static float Distance( const lem::MCollect<lem::Render::Point2di> &data1,
                          const lem::Render::Point2di &p );


   bool operator==( const Feature &x ) const; 
   bool Join( const Feature &x, int MaxFeatureSize, FeaturesMapping &mapping );

   bool Includes( const lem::MCollect<lem::Render::Point2di> &p ) const;
   bool Includes( const lem::Render::Point2di &p ) const;

   void RecalcPredicatesRel(void);

   void Draw( lem::Render::BmpBuffer &dc ) const;

   // �������� "���" ���������.
   inline int GetWeight(void) const { return CastSizeToInt(hit_points.size()); }

   inline real GetRel(void) const { return rel; }
  };


  extern lem::Render::BmpBuffer* load_bmp_c( int w, int h, const char *pix );


  typedef int PixelValue;

  enum MetaPixel { AnyPixel, Pixel0, Pixel1, NoPixel, OptionalPixel1 };


  // ********************************************************
  // ����������� �������� ����������� � ���� �����������
  // ��������� �� ��-��������
  // ********************************************************
  struct BaseBitmapEx
  {
   protected:
    BaseBitmapEx(void) {}

   public:
    virtual PixelValue get( int x, int y ) const=0;

    // ������� ����������� � ������ 1-���������� ������� �� ��-��������
    virtual int GetW(void) const=0;
    virtual int GetH(void) const=0;

    // ���������� ����� - human-friendly ������ � ��������� ����� (�������).
    virtual void Print( lem::OFormatter &to ) const=0;
  };


  struct ImageBitmapEx : public BaseBitmapEx
  {
   const lem::Render::Image* bmp;
   int w,h; // ������� �������� ��� ����� �������������� ������� ������ (��-�������)
   lem::uint8_t white_level; // ��������� ������� ������ (0-������, 255-�����)

   ImageBitmapEx( const lem::Render::Image* Bmp );

   ImageBitmapEx( int w, int h, const char *str );

   virtual PixelValue get( int x, int y ) const;

   virtual int GetW(void) const;
   virtual int GetH(void) const;
   virtual void Print( lem::OFormatter &to ) const;
  };


  struct ImageBitmapEx2 : public BaseBitmapEx
  {
   const lem::Render::Image* bmp;
   int w,h; // ������� ��������
   lem::uint8_t white_level; // ��������� ������� ������ (0-������, 255-�����)

   ImageBitmapEx2( const lem::Render::Image* Bmp );

   virtual PixelValue get( int x, int y ) const;

   virtual int GetW(void) const;
   virtual int GetH(void) const;
   virtual void Print( lem::OFormatter &to ) const;
  };

  struct ImageBitmapEx3 : public BaseBitmapEx
  {
   lem::BaseMatrix<int> mtx;
   int w,h; // ������� ��������

   ImageBitmapEx3( const lem::Render::Image* Bmp );

   virtual PixelValue get( int x, int y ) const;

   virtual int GetW(void) const;
   virtual int GetH(void) const;
   virtual void Print( lem::OFormatter &to ) const;
  };

  struct FloatBitmapEx : public BaseBitmapEx
  {
   const lem::FMatrix* bmp;
   int w,h;
   float white_level; // ��������� ������� ������

   FloatBitmapEx( const lem::FMatrix* Bmp );

   virtual PixelValue get( int x, int y ) const;

   virtual int GetW(void) const;
   virtual int GetH(void) const;
   virtual void Print( lem::OFormatter &to ) const;
  };







  class FeaturesMapping
  {
   public:
    lem::Ptr<BaseBitmapEx> bmp;
    lem::PtrCollect<Feature> features; // ��������� �� ����������� ���������
    lem::PtrCollect<Predicate> predicates; // n-����� ��������� (n>1)
    int w,h; // ������� ����������� (����� bmp)
    lem::MCollect< lem::MCollect<Feature*>* > pixels; // �������� ���������� � ��������

    FeaturesMapping(void);

    void Reset( const lem::Render::Image *Bmp );
    void Reset( BaseBitmapEx *Bmp );
    void Reset( const BaseBitmapEx *Bmp );
    void BuildPredicates( int MaxFeatureSize );

    void PrintFeatures( lem::OFormatter &to ) const;
    void PrintPredicates( lem::OFormatter &to ) const;
    void PrintPixels( lem::OFormatter &to ) const;
    lem::Render::BmpBuffer* DrawFeatures(void) const;

    void BindFeatureToPixel( const lem::Render::Point2di &p, Feature *f );
    void TrimFeaturesSet( int max_features_count );
  };


  struct DetectorHitAction
  {
   virtual void Do(
                   const FeatureDetector *detector,
                   const BaseBitmapEx *image,
                   int x,
                   int y,
                   const lem::MCollect<lem::Render::Point2di>& hit_points,
                   int miss_count
                  )=0;
  };

  
  class FeatureDetector
  {
   public:
    lem::PtrCollect<Predicate> predicates;
    lem::zbool is_line;
    int weight;
    int rank; // �������� ��� ������������ ���������� - �� ����� ����

   public:
    lem::UFString name; // �������� human-friendly ��� ���������
    lem::UFString ch; // ��� �������� ��� ������� ��������

   public:
    FeatureDetector(void);

    inline int GetWeight(void) const { return weight; }
    inline int GetRank(void) const { return rank; }

    virtual void Scan( const BaseBitmapEx *image, int MaxFeatureSize, FeaturesMapping &mapping ) const=0;
    virtual float Match(
                        const BaseBitmapEx *image,
                        int x, int y, 
                        float possible_mismatch, // ���������� ������ ������������ (0...1.0) 
                        lem::MCollect<lem::Render::Point2di> &hit_points
                       ) const { return 0.0; }

    virtual void Print( lem::OFormatter &to ) const=0;
    virtual void PrintName( lem::OFormatter &to ) const=0;
    virtual int GetW(void) const;
    virtual int GetH(void) const;
    virtual bool IsSubset( const FeatureDetector *maybe_subset ) const=0;

    virtual void SaveBin( lem::Stream &bin ) const;
    virtual void LoadBin( lem::Stream &bin );
  };




  class BmpFeatureDetector : public FeatureDetector
  {
   public:
    int w,h;
    int x0,y0; // ����������� ������ �������� (��� ������, ����� ���� ������������ �������)
    lem::BaseMatrix<int> pattern;

   public:
    lem::Path filepath; // �� ������ ����� ��� �������� ��������(�,�) ����(�,�) ���������
    lem::MCollect< const BmpFeatureDetector* > supersets;
    lem::MCollect< const BmpFeatureDetector* > subsets;
  
   public:
    BmpFeatureDetector(void);
    BmpFeatureDetector( int W, int H, const char *Str );
    BmpFeatureDetector( const BmpFeatureDetector &x );

    void operator=( const BmpFeatureDetector &x );

    virtual float Match(
                        const BaseBitmapEx *image,
                        int x, int y, 
                        float possible_mismatch, // ���������� ������ ������������ (0...1.0) 
                        lem::MCollect<lem::Render::Point2di> &hit_points
                       ) const;

    virtual void Scan( const BaseBitmapEx *image, int MaxFeatureSize, FeaturesMapping &mapping ) const;
    virtual int Scan( const BaseBitmapEx *image, DetectorHitAction *action, float possible_mismatch ) const;

    // ���������, �������� �� �������� maybe_subset ������������� ������� ��������.
    virtual bool IsSubset( const FeatureDetector *maybe_subset ) const;

    virtual int GetW(void) const;
    virtual int GetH(void) const;

    virtual void Print( lem::OFormatter &to ) const;
    virtual void PrintName( lem::OFormatter &to ) const;

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    inline int get( int x, int y ) const { return pattern.get(y,x); }
    inline int set( int x, int y, int px ) { return pattern.set(y,x,px); }
  };




  class RealBmpFeatureDetector : public BmpFeatureDetector
  {
   public:
    RealBmpFeatureDetector( const lem::Path &image_filename );
  };



  struct SymbolFeatureSet;


 // ***************************************************
 // ����� ���������� � ����������, ���������������
 // ���� ������.
 // ***************************************************
 struct SymbolFeatureSet
 {
/*
  struct OptimizationIterator
  {
   int count, total;
   
   OptimizationIterator(void) { count=total=0; }
   
   inline bool operator()(void) const { return count<total; }
   inline void operator++(void) { count++; }
  };*/

  int complexity; // ��������� ������� ����������
  int arity; // ������������ ������� ����������
  int var_count; // ���-�� ����������, ����������� ������� ����������� (����� ���
                 // ���-�� ������������ ���������� _0, _1, _2 ... )
 
  lem::PtrCollect<PredicateTemplate> predicates;
  int isignal; // ����� ������ ������������

  // ��� ��������� ����������.
  std::map<int /*��� ���������*/,int /*������� ��� ��������*/> inames;
  void BuildHash();
 

  SymbolFeatureSet(void);
  SymbolFeatureSet( const FeaturesMapping &mapping, int MinFeautreSize );
  SymbolFeatureSet( const SymbolFeatureSet &x );

  void operator=( const SymbolFeatureSet &x );

  int Complexity(void) const { return complexity; }
  int Arity(void) const { return arity; }

  bool operator==( const SymbolFeatureSet &x ) const;
  bool operator!=( const SymbolFeatureSet &x ) const;

  bool CanBeUnifiedWith( const SymbolFeatureSet &x ) const;

  bool ReduceComplexity(void);

  void SaveBin( lem::Stream &file ) const;
  void LoadBin( lem::Stream &file );

  void ListPredicates( lem::OFormatter &to ) const;
 };


 struct PredicateDetector
 {
  int predicate_name;
  int n_arg;
  int arg0, arg1, arg2;
  int ioutput;

  bool match( const PredicateTemplate &x ) const;  
 }; 


 class FeaturesAlceptor : public AlgoAlceptor
 {
  private:
   int max_features_count;

   lem::MCollect<PredicateDetector> detectors;

  public:
   FeaturesAlceptor( int iOffset, int MaxFeaturesCount, int _outer_raster_w, int _outer_raster_h );
   FeaturesAlceptor( lem::Stream &bin );
   FeaturesAlceptor( const FeaturesAlceptor &x );

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   virtual void FixInput( Pattern &pattern );
   virtual Alceptor* clone(void) const;
 };




 struct RecognitionError
 {
  // ����� ���������� ���������� ������� � ����� ������������
  // ���������, ���������� ������ ������ ����� �������� ������
  // ��� ���������� ���������.
  lem::zint total_hits;
  lem::zint positive_hits;
  lem::zint total_errors;
  lem::zint positive_errors;
 };


 struct MaskLearnImage : lem::NonCopyable
 {
  lem::Path image_path;
  int isignal;
  lem::UFString group;
  int side_border;
  lem::zbool generate_hash;

  MaskLearnImage(void) { isignal=UNKNOWN; side_border=UNKNOWN; }
 };



struct HashBuildOpt
{
 int h1,w1;
 HashBuildOpt(void)
 {
  h1 = 2;
  w1 = 0;
 } 
};

class HashDetector : public BmpFeatureDetector
{
 public:
  HashDetector(void) {}

  HashDetector( const BmpFeatureDetector *src, const HashBuildOpt &opt )
   : Solarix::Ocr::BmpFeatureDetector()
  {
   h = lem::_min( opt.h1, src->GetH() );
   
   if( opt.w1==0 )
    w = src->w;
   else
    w = lem::_min( opt.w1, src->GetW() );
    
   x0=0;
   y0=0;
   
   pattern = lem::BaseMatrix<int>( h, w );
   
   for( int y=0; y<h; ++y )
    for( int x=0; x<w; ++x )
     {
      const int px = src->pattern.get(y,x);
      pattern.set( y, x, px );
     }
     
   return;
  }

  HashDetector( const HashDetector &d ) : BmpFeatureDetector(d) {}

  void operator=( const HashDetector &d )
  {
   BmpFeatureDetector::operator=(d);
   return;
  } 

  void SaveBin( lem::Stream &bin ) const
  {
   Solarix::Ocr::BmpFeatureDetector::SaveBin(bin);
   return;
  }

  void LoadBin( lem::Stream &bin )
  {
   Solarix::Ocr::BmpFeatureDetector::LoadBin(bin);
   return;
  }

  bool operator==( const HashDetector &x ) const
  {
   return w==x.w && h==x.h && pattern==x.pattern;
  }

  bool MatchDetector( const BmpFeatureDetector *src ) const
  {
   if( w>src->w || h>src->h )
    return false;

   for( int y=0; y<h; ++y )
    for( int x=0; x<w; ++x )
     {
      const int px1 = src->pattern.get(y,x);
      const int px2 = pattern.get(y,x);

      if( px1!=px2 )
       return false;
     }

   return true;
  }
};



 struct MaskDetectors : lem::NonCopyable
 {
  lem::UFString group;
  lem::Ptr_NC_Collect<Solarix::Ocr::BmpFeatureDetector> list;
  int min_h, max_h, min_w, max_w;

  lem::PtrCollect<HashDetector> hashes;
  lem::MCollect<int> det_2_hash;

  MaskDetectors(void)
  {
   min_h=min_w=lem::int_max;
   max_h=max_w=0;
   return;
  }

  void SaveBin( lem::Stream &bin ) const;
  void LoadBin( lem::Stream &bin );

  void push_back( Solarix::Ocr::BmpFeatureDetector *x ) { list.push_back(x); }
  lem::Container::size_type size(void) const { return list.size(); }
  const Solarix::Ocr::BmpFeatureDetector* operator[]( int i ) const { return list[i]; }
        Solarix::Ocr::BmpFeatureDetector* operator[]( int i )       { return list[i]; }

  lem::Ptr_NC_Collect<Solarix::Ocr::BmpFeatureDetector>::iterator begin(void) { return list.begin(); }
  lem::Ptr_NC_Collect<Solarix::Ocr::BmpFeatureDetector>::iterator end(void) { return list.end(); }

  const Solarix::Ocr::BmpFeatureDetector* front(void) const { return list.front(); }
  const Solarix::Ocr::BmpFeatureDetector* back(void) const { return list.back(); }
 };

 struct MaskTrainerOptions
 {
  lem::zbool autogenerate_redpixels;
  lem::zbool generate_hashes;
  lem::zint side_border;
  int masks_border;
  int montecarlo; // ����� �������� ��������� ����� ������� �����-����� �� ���� �������

  MaskTrainerOptions(void) { masks_border=1; montecarlo=0; }
 };

 struct MaskGroupInfo : lem::NonCopyable
 {
  lem::UFString name;
  lem::Path images;
  lem::Path ngrams; // ����� � n-�������� �������� ��� ������������ �������� ��������� 
  lem::Path words; // ����� � ��������� �������������� ��� �������� ���-�����

  MaskGroupInfo(void) {}
 };


 // *****************************************************************
 // ��� ������ �������������, ������������� ��� ����������� ���������
 // � ��������� ��� �������� � �������������.
 // *****************************************************************
 class LetterRecognizer
 {
  public:
   lem::zbool use_masks_trainer;
//   int masks_border;
   int raster_w, raster_h; // ��� ������ � �������������
   int input_char_w, output_char_w; // ��� ������ � ���������� ����������

  private:
   int aperture_w;
   int n_output, n_input;

   lem::FMatrix mask; // ����������� ��������

   int aperture_span;

   void LoadSessions( const lem::Xml::Parser &parser, const wchar_t *xml_node, const lem::Collect<lem::UFString> & tags, Patterns &store );

   lem::Ptr_NC_Collect<MaskLearnImage> learn_masks;
   lem::Ptr_NC_Collect<MaskDetectors> mask_groups;
   lem::Ptr_NC_Collect<MaskGroupInfo> mask_groups_info;
   
   void LoadSessions(
                     const lem::Xml::Parser &parser,
                     const wchar_t *xml_node,
                     const lem::Collect<lem::UFString> & tags,
                     lem::Ptr_NC_Collect<MaskLearnImage> &storage
                    );
  

  // ************************************************
  // �������� ��������� ������������� ���������� ���
  // ������������� ��������.
  // ************************************************
  private:
   lem::PtrCollect<FeatureDetector> detectors;

   void SortDetectors(void);
   void AddDetectors_VLine(void);
   void AddDetectors_HLine(void);
   void AddDetectors_LSlop(void);
   void AddDetectors_RSlop(void);
   void AddDetectors_Arc(void);
   void AddDetectors_Circle(void);
   void AddDetectors_T(void);
   void AddDetectors_L(void);
   void AddDetectors_X(void);

  public:
   void AddDetectors(void);

   lem::OFormatter *logfile;

   // �������� ��������� ����
   lem::Ptr<NeuroNet> net;

   lem::PtrCollect<SymbolFeatureSet> feature_recognizers; // ���������-���������� ��������������
   
   // ���������� ���� - ������������ ��� �������� ��� sliding sessions ����������
   lem::Ptr<NeuroNet> aperture_net;

   lem::zbool random_learning; // �������� ���������� ��������� �������� (����� - ���������������)

   Patterns learn_patterns; // ������� ��������
   Patterns test_patterns; // ����������� ��������

   lem::Collect<Signal> signals;
   lem::PtrCollect<CharSignal> chars;
   static lem::Math::RandU rnd;

   lem::Path outdir; // ������� ��� ������ ������������ ������ �������, �����������...

   lem::zbool autogenerate_shifted_patterns; // ������������� ������������ ���� ���������
                                             // �������� � �������, ����� �������� ������� ����� ������ ����.
   

  public: 
   LetterRecognizer(void);
   LetterRecognizer( int W, int H );

   void LoadGeometry( const lem::Xml::Parser &parser, const lem::Xml::Node *options );
   void LoadSignalDefinitions( const lem::Xml::Parser &xml, const lem::Xml::Node *options );
   void LoadCharsDefinitions( const lem::Xml::Parser &parser, const lem::Xml::Node *chars_node );

   void LoadSessions( const lem::Xml::Parser &xml, const lem::Collect<lem::UFString> & tags );

   int CountLearnPatterns(void) const;
   int CountTestPatterns(void) const { return CastSizeToInt(test_patterns.size()); }

   void TrainMasks( const MaskTrainerOptions &opt );

   real LearnStaticSessions(void);
   RecognitionError CalcErrors(void);

   real Learn( const lem::Path &filepath, int Signal );

   bool TestStaticSessions( real &err, RecognitionError &res );

   // ������-�������� ����������� ������� �� ������ ������������� ���������.
   void FindMostFaulty( lem::PtrCollect< IncorrectRecognition > &res );

   // **************************************************************
   // ��������� �������� � �������������� ��������� ���� ����������.
   // **************************************************************
   void LoadInputImage( const lem::Path &filename );

   // ���������� ������ �������� ���������� �������� �������������,
   // � ����� ��� �������������
   std::pair<int,real> Recognize(void) const;
   
   void Recognize( InputBitmap &input_signals, const RecognitionOptions &params );
   void Recognize( Pattern &pattern, const RecognitionOptions &params );
   
   // ������������ ������� ������ �������������.
   real CalcError( int isignal ) const;

   // ���������� ������������ ���� � �������� �����
   void SaveBin(
                lem::Stream &bin,
                bool save_neuronet,
                bool save_formal_recognizers
               ) const;

   // ��������� C-���� ��� ���������� ������� �������������
   void SaveC( lem::OFormatter &out ) const;

   void LoadBin( lem::Stream &bin, bool recreate=true );
   static NeuroNet* LoadNet( const lem::Path &filename );

   void Optimize(void);

   void Analyze( lem::OUFormatter &to );

   int FindSignal( const lem::UFString &x ) const;
   inline const Signal& GetSignalInfo( int i ) const { return signals[i]; }

   int FindChar( wchar_t c ) const;

   inline int GetRasterW(void) const { return raster_w; }
   inline int GetRasterH(void) const { return raster_h; }

   void BuildMaskMatrix( lem::FMatrix &mask );
   void TrainingBegins(void);

   void RunFeatureTraining(void);
   void ProcessImage( const lem::Render::Image *image, FeaturesMapping &mapping, int MaxFeatureSize, int predicates );
   void ProcessImage( const BaseBitmapEx *image, FeaturesMapping &mapping, int MaxFeatureSize, int predicates );

   SymbolFeatureSet* BuildSymbolPredicates( const lem::Render::Image *img1, FeaturesMapping& mapping, int max_features_count, bool predicates );
   SymbolFeatureSet* BuildSymbolPredicates( const lem::Path &p, int max_features_count, bool predicates );
   SymbolFeatureSet* BuildSymbolPredicates( const BaseBitmapEx *img1, FeaturesMapping& mapping, int max_features_count, bool predicates );

   std::pair<SymbolFeatureSet*,FeaturesMapping*> DetectFeatures2( const lem::Path &p, int max_features_count, bool predicates );
   std::pair<SymbolFeatureSet*,FeaturesMapping*> DetectFeatures2( const lem::Render::Image *img1, int max_features_count, bool predicates );

   void RemoveLayer( int layer_index );
 };

  
  } // namespace Ocr
 } // namespace Solarix

#endif
