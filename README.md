This project is dated 2000-2001 and is for WinAmp 2

Below is screenshots and the original readme file:

![Main window](/_screenshots/2.png)

![WinAmp view](/_screenshots/1.png)

```
=[ common information ]=======================================================

 (1) this plug-in is useful for fido users  to  insert  into  their  messages
 lines  such as "np: Guano Apes -- Lords of the boards". it  creates  a  file
 which contains a single text line generated from your template and  you  can
 do with it whatever you want
 
 (2) author of this plug-in -- michael samoylenko:
 email: powermike@narod.ru
 fido:  2:5064/33.25

=[ how to use ]===============================================================

 to configure plug-in, go to 
 Winamp Preferences -> Plugins -> General Purpose -> PowerMike's Fido Plug-In

 there are many ways of how to use this plug-in with various editors.see your
 editor's documentation to learn how to insert a text from an  external  file
 into your message

 ( golded )
 the most common way is to insert your winamp info into the tearline:

=== cut ===
 From : Michael Samoylenko   
------------------------------------------------------------------------------

>[skip]

--- [ now playing ] :: Eminem / Stan
 * Origin: Open up your mind and let me step inside (2:5064/33.25)

=== cut ===

 in  golded.cfg,  you'll  need to change your tearline for inserting it from an 
 external file. for example,

 tearline My Unbekewlable Tearline

 to

 tearline @c:\fido\golded\lsts\winamp.lst

 where "c:\fido\golded\lsts\winamp.lst" - path to plug-in's output file, 
 '@' - golded's token for insertion random string from an external file
 ( see golded documentation )
```
