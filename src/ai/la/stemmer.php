<script language="php">
function stem( $word )
{
$uword = strtolower($word);
$wordlen = strlen($word);
if($wordlen<3) return $uword;
$last_ch = substr($uword,$wordlen-1,1);
$prev_ch = substr($uword,$wordlen-2,1);
$sfx2=substr( $uword, $wordlen-2, 1 );
$sfx3=substr( $uword, $wordlen-3, 2 );
$sfx3_2=substr( $uword, $wordlen-3, 1 );
$sfx4=substr( $uword, $wordlen-4, 3 );
$sfx4_2=substr( $uword, $wordlen-4, 2 );
$sfx6=substr( $uword, $wordlen-6, 5 );
$sfx6_2=substr( $uword, $wordlen-6, 4 );
$sfx7=substr( $uword, $wordlen-7, 6 );
$sfx7_2=substr( $uword, $wordlen-7, 5 );
$sfx5=substr( $uword, $wordlen-5, 4 );
$sfx5_2=substr( $uword, $wordlen-5, 3 );
$sfx8=substr( $uword, $wordlen-8, 7 );
$sfx8_2=substr( $uword, $wordlen-8, 6 );
$sfx10=substr( $uword, $wordlen-10, 9 );
$sfx10_2=substr( $uword, $wordlen-10, 8 );
$sfx9=substr( $uword, $wordlen-9, 8 );
$sfx9_2=substr( $uword, $wordlen-9, 7 );
$sfx11=substr( $uword, $wordlen-11, 10 );
$sfx11_2=substr( $uword, $wordlen-11, 9 );

 if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx9_2,"�������")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx9_2,"�������")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx11_2,"���������")==0 )
 return substr($word,0,$wordlen-11);
   if( strcmp($sfx9_2,"�������")==0 )
 return substr($word,0,$wordlen-9);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx10_2,"��������")==0 )
 return substr($word,0,$wordlen-10);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx7_2,"�����")==0 )
 return substr($word,0,$wordlen-7);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx8_2,"������")==0 )
 return substr($word,0,$wordlen-8);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx6_2,"����")==0 )
 return substr($word,0,$wordlen-6);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx5_2,"���")==0 )
 return substr($word,0,$wordlen-5);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx4_2,"��")==0 )
 return substr($word,0,$wordlen-4);
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
   if( strcmp($sfx3_2,"�")==0 )
 return substr($word,0,$wordlen-3);
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
else  if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
 }
 }
else  if($last_ch=='�')
  {
      return substr($word,0,$wordlen-1);
 }
else  if($last_ch=='�')
  {
 if( $prev_ch=='�' )
  {
       return substr($word,0,$wordlen-2);
 }
 else
     {
      return substr($word,0,$wordlen-1);
 }
 }
return $uword;
}
</script>
