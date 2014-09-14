// -----------------------------------------------------------------------------
// File LEM_EDLI.CPP
//
// (c) Koziev Elijah, Obninsk-Cherepovets, Russia, 1995-2002
//
// Content:
// ���⥭쪨� ⥪�⮢� ����� ।���� - �ᯮ������ ��� �࣠����樨 �����
// �����⭮�� ����� ������ � �ନ����, ����� �⠭���⭮� ��⥬��� ��楤���.
// -----------------------------------------------------------------------------
//
// CD->17.05.96
// LC->19.04.02
// ------------

#include <conio.h>
#include <signal.h>

#include <lem_scan.h>
#include <lem_mstr.h>


using namespace lem;

// ***********************************************************************
// �᫨ psw=true, � ������� ᨬ���� ���������� �� �࠭� ᨬ����� '*'.
// �� ���筮 �ᯮ������ �� ����� ��஫��.
// ***********************************************************************
const FString lem::edline( const char *question, const bool psw )
{
 int pos=0;
 mout.printf( "%s", question );

 FString buffer;

 #if defined LEM_WATCOM

 bool cont=true;

 while(cont)
  {
   char ch=getch();

   switch(ch)
    {
     case '\r':
      // ��୥� ⥪���� ��ப�.
      cont=false;
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // ����� 'ESC' - ���⨬ ���� � ��୥� ������ ��ப�.
       buffer="";
       cont=false;
       break;
      }

     case '\b':
      {
       // '<-'
       if( buffer.len() )
        {
         pos--;
         buffer.remove(pos);

         mout.printf( "'\b'" );
        }

       break;
      }

     case 0:
       getch();
       break;

     default:
       {
        buffer.set(pos,ch);

         if( psw )
          mout.printf( "*" );
         else
          mout.printf( "%c", ch );

        break;
       }
    }
  }

 #elif defined LEM_SYMANTEC || defined LEM_DJGPP

  // ���� ��஫�� �� ॠ�������.
  LEM_CHECKIT_Z( psw=false );

  char *b = new char[128];
  lem_check_ptr(b);
  gets( b );
  buffer=b;
  delete b;

 #else

 bool cont=true;
 bool insert=true;

 int x0=wherex(), y0=wherey();

 while(cont)
  {
   int x=wherex(), y=wherey();
   char ch=getch();

   switch(ch)
    {
     case '\r':
      // ��୥� ⥪���� ��ப�.
      cont=false;
      mout.eol();
      break;

     #if !defined LEM_BORLAND_3_1
     case 3: // Ctrl-C
       raise(SIGBREAK);
       buffer="";
       cont=false;
       break;
     #endif

     case 27:
      {
       // ����� 'ESC' - ���⨬ ���� � ��୥� ������ ��ப�.
       buffer="";
       cont=false;
       mout.eol();
       break;
      }

     case '\b':
      {
       // '<-'

       if( pos>0 )
        {
         pos--;
         buffer.remove(pos);
         gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

         gotoxy(x-1,y);
        }

       break;
      }

     case 0:
      {
       ch=getch();

       switch(ch)
        {
         case 'K':
          if(pos>0)
           {
            pos--;
            gotoxy(x-1,y);
           }
          break;

         case 'M':
          if(pos<buffer.len())
           {
            pos++;
            gotoxy(x+1,y);
           }
          break;

         case 'R':
          #if !defined LEM_WINDOWS
          if( insert=!insert )
           _setcursortype(_NORMALCURSOR);
          else
           _setcursortype(_SOLIDCURSOR);
          break;
          #endif

         case 'S':
          buffer.remove(pos);
          gotoxy(x0,y0);

          if( !psw )
           mout.printf( "%lS ", buffer );
          else
           mout.printf( "%H* ", buffer.len() );

          gotoxy(x,y);
          break;
        }

       break;
      }

     default:
      if( insert )
       {
        // ����� ��⠢�� ᨬ�����
        buffer.insert(pos,ch);
        gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

        gotoxy(x+1,y);
        pos++;
       }
      else
       {
        // ����� 'overwrite'
        buffer.set(pos,ch);
        gotoxy(x0,y0);

         if( !psw )
          mout.printf( "%lS ", buffer );
         else
          mout.printf( "%H* ", buffer.len() );

        gotoxy(x,y);
       }
    }
  }
 #endif

 return buffer;
}

// -------------------------- End Of File [LEM_EDLI.CPP] -----------------------
