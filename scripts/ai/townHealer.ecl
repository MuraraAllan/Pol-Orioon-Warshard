CE                           basic       lower                            CInt                             SplitWords                       CDbl                             CStr                             find                             len                              Hex                                   basicio           npc         SetAnchor                        Self                              TurnToward                            os          sleepms                          getprocess                       start_script                     set_critical                     syslog                           set_priority                     wait_for_event                   sleep                                 uo       *   GetObjProperty                   SendEvent                        PrintTextAbove                   SendDialogGump                   MoveCharacterToLocation          RecalcVitals                     GetAttributeBaseValue            SetObjProperty                   SetAttributeBaseValue            AlterAttributeTemporaryMod       GetAttribute                     GetAttributeTemporaryMod         GetAttributeIntrinsicMod         GetVital                         GetVitalMaximumValue             GetVitalRegenRate                SetAttributeTemporaryMod         SetVital                         SendSysMessage                   EnumerateItemsInContainer        FindStorageArea                  CreateStorageArea                FindRootItemInStorageArea        CreateRootItemInStorageArea      CheckLosAt                       ListEquippedItems                DestroyItem                      CreateItemAtLocation             MoveItemToContainer              EquipItem                        Distance                         MoveItemToLocation               DestroyRootItemInStorageArea     EnableEvents                     DisableEvents                    PlayObjectCenteredEffect         PlaySoundEffect                  HealDamage                       CheckLineOfSight                 PerformAction                    Resurrect                        GetEquipmentByLayer                   util        RandomInt                        RandomDiceRoll                        cfgfile     ReadConfigFile                   FindConfigElem                   GetConfigInt                     GetConfigString                  GetConfigStringArray                  math        Pow                              Log10                             �  �  +   :     9     9     9     9   /  9   N  9   m  9         +  :     9         +  �        +     +     +      �  /     +  /         �   �  !/      �   �  !/      �   �  !/      �  "/     4  �   �   �  /      �  %V  *       �  /  K   3   %T  3   M�  7�  3   M�   �  ;�  &T  3   M�  !   "W     $  '>      #�  3   M�     3   M�        3   M    %�  3   /     4       /        /     3       $  ( #/     3    , $/     3    0 4  B !   ",     F (   3   M�  3   M�     %�  3   /     4  J  q  u /      y (   3   M�     3   M�     %�  3   /     4  }  �  � /      � (   3   !   "]  �    3   M�        3   M�     %�  3   /     4  }  �  � /      � (   3   !   "]  �    3   M�        3   M�        %  3   /     4  �  �  � /      �  /     *   � /        4  �  �  � /      �  /     3   3  %/     3   � 3     �     �   /     3         #/     3     $/       (   $  3   M�  4  3   &/     3   M�        %* 3   /     4    ;  ? /      C /     4   G '/     4   K $/     3    O (/     3    S )/  /      W (    [ (   #_ #e #p #�  *  F         3  �        3  w       3  p       3  e       3  _       3   | O�  3  3  Op 3  3  Oe 3  3   O_ 3   � !   "e 3  ;�     � (   #� 3   � /   �    /   (   #� #�  *  3  �  /  /         *  3  /        3     3         %� � :   3  9   /  K  3  M� %� 3  � 3  M�     �  � /     3  (      �   page 0 nodispose noclose gumppic 300 230 2070 button 330 305 2073 2072 1 0 0 button 400 305 2076 2075 1 0 1 text 332 264 40 0 Resurrect Now? �������?2      ����   ����         Criado.... 	        x   type source    isa J �   T �mobile criminal dead poisoned An Nox 	     �  Z7          x   defaultPoison d      Limpe seus pecados e poderei ajuda-lo! 	        Saia daqui seu criminoso! 	        <   	        <   A compaixao cura a todos! 	     �  1d15+17 In Vas Mani 	     �    	   �  Z7             Volte a vida por suas virtudes! 	                          level poisontype amount name        sendevent     who Life d   no_start #PoisonPID :poisonwatcher:poisonwatcher errortext Poison Watcher GetScript()  	     