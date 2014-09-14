#ifndef SCAN_OPTIONS__H
#define SCAN_OPTIONS__H
#pragma once

 #include <lem/zeroed.h>
 #include <lem/streams.h>
 #include <lem/url.h>
 #include <lem/unicode.h>
 #include <lem/containers.h>
 #include <lem/ptr_container.h>
 #include <lem/smart_pointers.h>
 #include <lem/solarix/se_plugin_options.h>
 #include <lem/solarix/se_doc_preprocessor.h>
 #include <lem/solarix/se_file_filter.h>
  
 namespace Solarix
 {
  namespace Search_Engine
  { 


  #if defined FAIND_OCR
  struct OCRParams
  {
   lem::zbool use;
   lem::UFString params;

   OCRParams(void);
   OCRParams( const OCRParams &x ); 
   void operator=( const OCRParams &x ); 
 
   void clear(void);

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );
  };
  #endif

  // *************************************************
  // ��������� ���������� ������������ ��������������
  // *************************************************
  struct MetaInfoParams
  {
   lem::zbool enabled; // ������������ �������� ���������� �������� ������ �� ���������� � ������
   lem::UFString u_metafilename; // ��� ���������
   lem::FString a_metafilename;
   typedef enum { UnknownFormat, XmlFormat, CsvFormat } FormatType;
   FormatType format; // ������

   typedef enum { StoreInCache, StoreInServer } StorageType;
   StorageType storage;

   static wchar_t *Tagname;

   MetaInfoParams(void);
   MetaInfoParams( const MetaInfoParams &x );
   void operator =( const MetaInfoParams &x );

   void clear(void);

   void SaveBin( lem::Stream &bin ) const;
   void LoadBin( lem::Stream &bin );

   bool IsMetafile( const wchar_t *filename ) const;
   bool IsMetafile( const char *filename ) const;
  };


  // *****************************
  // Files filtering options.
  // ����� �� ���������� ������.
  // *****************************
  struct Scan_Options
  {
   private:
    #if LEM_DEBUGGING==1
    lem::Guardian guard;
    #endif

    lem::MCollect<int /*bool*/> del_file_filter;

    void Init( const Scan_Options &x );

   public:
    lem::Collect<lem::UFString> cmd_args; // ������ ��������� ������, �� ������� ��������� ���������
   
    bool recurse;             // ����������� �����������
    bool follow_href;         // ��������� �� ������������
    int href_depth;           // ����. ����� ������� �� �����������   
    int limit_traffic;        // ����������� �� ��������� ������� �� ������  
    bool unpack;              // ������������� � ������������ ������
    lem::zbool skipfiles; // ��������� ���������� ��������� ������

    bool allow_raw;           // ����� �� �������� � ������� ����������� ��������
    lem::Collect<lem::UFString> raw_ext; // ����������, ������� �������������� raw �������

    bool allow_gfx;           // ����� ������������ ����������� �����
    bool allow_video;         // ����� �� ������������ ����������   
    bool allow_audio;         // ����� �� ������������ ����������   
    bool allow_exec;          // ����� �� ������������ ���������� ����� (exe, dll)
    bool store_all_files;     // � ��������� ���� ��������� �������� � ���� ������ (���� �� ������������ ��������)
    bool fn_cased;            // ������ ��������� ������� ���� � ������ ������
    bool org_domain;          // �� ������� �� �������� �� �������� �����
    bool strip_decoration;    // ������� ���� XML/HTML, RTF � ��� ����� 
    bool process_contents;    // ������������� �� ���������� ����������, ��� ������������ ������ ������� ������
 
    lem::Collect<lem::UFString> folder; // �������� ��� ���������
    lem::Collect<lem::UFString> file;   // ����� ��� ���������
    lem::Collect<lem::UFString> engine; // ������� ���������� (�������) � ��������� ��������
    bool manual_sources; // ��� ���������� ���������� � ������ �� ������ �� �����������
                         // ���� � ��� �� ���������� ������ ���� ������ ��� ��������� ���
                         // ���������, �� ������� ������ �� �����.
    lem::zbool locate_mode; // ��������� "locate"

    lem::Collect<lem::UFString> file_regex_mask;        // ����� ��� �������������� ������ - ��������
    lem::Collect<lem::UFString> file_wildcards_notmask; // ����� ���������� ��� �������������� ������ - ������� ����� ������
    lem::Collect<lem::UFString> file_regex_notmask;     // ����� ���������� ��� �������������� ������ - ��������
    lem::Collect<lem::UFString> file_wildcards_mask;    // ����� ��� �������������� ������ - ������� ����� ������

    #if defined FAIND_WEB
    lem::Collect<lem::Url> uri;       // ������ ���������� � ���������
    lem::Collect<lem::UFString> uri_mask, uri_notmask;  // ����� ��� URI
    #endif

    #if defined FAIND_NETWORKING 
    lem::Collect<lem::UFString> pipe;      // ����� �������
    lem::Collect<lem::UFString> socket;    // ������ �������
    #endif

    lem::MCollect<Base_File_Filter*> file_filter; // ����������� ���������������� �����
                                             // ���������� ������� ��� ������

    lem::MCollect<Base_File_Filter*> file_notfilter; // ����������� ���������������� �����
                                                // ���������� ������� ���������� ��� ������

    lem::MCollect<Base_File_Filter*> all_file_filters; // ��� ������� ��� ������,
                              // ������� ��������������� ����� ����� � �����������
                              // ���������������� �����.

    #if defined FAIND_WEB
    lem::MCollect<Base_File_Filter*> all_uri_filters; // ��� ������� ��� URI
    lem::UFString proxy_server; // ���� ��� ������ � �������� ������������ ������� - ��� �����
    lem::UFString proxy_bypass; // �����, ������ � ������� ���� �� ����� �������
    bool passive_ftp; // PASSIVE FTP mode
    #endif

    lem::zbool store_download;   // ��������� ����������� �� ��������� ��������� �
    lem::UFString download_dir;  // ���� ��������.

    lem::CString forced_cp_name; // ������������� �������� ������� �������� ��� ���������� 
    const lem::CodeConverter *forced_cp;
    lem::Ptr<lem::Transliterator> translit; // ���� ����� ������������ �������������� �������� �������
    
    lem::Collect<lem::UFString> prefer_cp_names; // ��������������� ��� �������� � CodeGuesser'� ������� ��������
    lem::MCollect<const lem::CodeConverter*> prefer_cp_list; // ��������� �� ������� ������� �������


    lem::PtrCollect<Doc_Preprocessor> preprocessor; // ������ ���������� ��������� ���������� ����� �� ������� � �����/����������

    lem::zbool force_txt; // ������������ ��� ����� ��� ������� plain text
    lem::zbool force_binhex; // ��������������� ����� ��� ��������� ������ ������

    PluginOptions plugin_options; // ������ ���������� ��� �������� � �������

    #if defined FAIND_OCR
    OCRParams ocr; // ��������� ���������� OCR �������
    #endif

    MetaInfoParams metainfo;

    Scan_Options(void);
    Scan_Options( const Scan_Options &x );

    ~Scan_Options();

    void operator=( const Scan_Options &x );

    // ��������� ���������� ��������� ����� �������� ��������� ������
    void Prepare(void);

    // ������� ��� ����
    void Clear(void);

    void SaveBin( lem::Stream &bin ) const;
    void LoadBin( lem::Stream &bin );

    // Is search domain empty?  
    bool IsEmptyDomain(void) const;

    // Is there any filters defined?
    inline bool Filters(void) const
    {
     return !all_file_filters.empty()
            #if defined FAIND_WEB
            || !all_uri_filters.empty()
            #endif
            ; 
    }

    // ������ true � �������� �����, ���� � �������� ���� ������
    // ���������� CD/DVD ������
    bool Refers_Cdrom( lem::uint32_t &SerialNumber, lem::FString &drive ) const;
    bool Refers_Cdrom( const lem::UFString &path, lem::uint32_t &SerialNumber, lem::FString &drive ) const;
  };

 }
}
#endif
