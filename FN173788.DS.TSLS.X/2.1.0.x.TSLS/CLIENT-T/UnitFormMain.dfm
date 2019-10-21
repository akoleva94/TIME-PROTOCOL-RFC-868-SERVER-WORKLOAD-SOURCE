object formMain: TformMain
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = ' Time Server Load Simulator'
  ClientHeight = 401
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object panelShowHideProtocol: TPanel
    Left = 0
    Top = 53
    Width = 505
    Height = 12
    Margins.Left = 2
    Margins.Top = 2
    Margins.Right = 2
    Margins.Bottom = 2
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 500
    object labelShowHideLog: TLabel
      Left = 10
      Top = -1
      Width = 11
      Height = 12
      Cursor = crSizeNS
      Hint = 'Show/Hide Log'
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Caption = '+ '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      OnClick = labelShowHideLogClick
    end
    object bevelShowHideProtokol: TBevel
      Left = 22
      Top = 4
      Width = 475
      Height = 2
      Margins.Left = 2
      Margins.Top = 2
      Margins.Right = 2
      Margins.Bottom = 2
      Align = alCustom
      Anchors = [akLeft, akRight]
      Shape = bsBottomLine
      Style = bsRaised
      ExplicitWidth = 490
    end
  end
  object gbSync: TGroupBox
    Left = 0
    Top = 0
    Width = 505
    Height = 53
    Align = alTop
    TabOrder = 1
    ExplicitWidth = 500
    object buttonSync: TButton
      Left = 2
      Top = 15
      Width = 501
      Height = 36
      Align = alClient
      Caption = 'S Y N C'
      TabOrder = 0
      OnClick = buttonSyncClick
      ExplicitWidth = 496
    end
  end
  object gbLog: TGroupBox
    Left = 0
    Top = 65
    Width = 505
    Height = 315
    Align = alClient
    Caption = ' Log '
    TabOrder = 2
    ExplicitWidth = 500
    object memoLog: TMemo
      Left = 2
      Top = 15
      Width = 501
      Height = 298
      Align = alClient
      PopupMenu = pupLog
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      ExplicitWidth = 496
    end
  end
  object stBarReport: TStatusBar
    Left = 0
    Top = 380
    Width = 505
    Height = 21
    Panels = <
      item
        Alignment = taCenter
        Width = 75
      end
      item
        Alignment = taCenter
        Width = 300
      end
      item
        Alignment = taCenter
        Width = 130
      end
      item
        Alignment = taCenter
        Width = 50
      end>
    ExplicitTop = 384
    ExplicitWidth = 556
  end
  object pupLog: TPopupMenu
    Left = 24
    Top = 96
    object miClearLog: TMenuItem
      Caption = 'Clear Log'
      OnClick = miClearLogClick
    end
    object miSaveLog: TMenuItem
      Caption = 'Save Log'
      OnClick = miSaveLogClick
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object miSaveReport: TMenuItem
      Caption = 'Save Report'
      OnClick = miSaveReportClick
    end
  end
end
