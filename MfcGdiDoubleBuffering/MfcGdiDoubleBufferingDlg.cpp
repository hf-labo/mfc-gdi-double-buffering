#include "pch.h"
#include "framework.h"
#include "MfcGdiDoubleBuffering.h"
#include "MfcGdiDoubleBufferingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMfcGdiDoubleBufferingDlg::CMfcGdiDoubleBufferingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGDIDOUBLEBUFFERING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcGdiDoubleBufferingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcGdiDoubleBufferingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMfcGdiDoubleBufferingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	this->SetTimer(WM_USER + 0x0001, 50, nullptr);

	return TRUE;
}

void CMfcGdiDoubleBufferingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	if (this->GetSafeHwnd())
	{
		static double rot = 0;
		double div = 2.0 * 3.141592653 / 90.0;
		rot += div;
		if (rot >= 2.0 * 3.141592653) rot -= 2.0 * 3.141592653;

		CDC* pDC = this->GetDC();
		CRect rc;
		CDC memDC;
		CBitmap memBmp;

		this->GetClientRect(rc);
		memDC.CreateCompatibleDC(pDC);
		memBmp.CreateCompatibleBitmap(pDC, rc.Width() / 2, rc.Height());
		CBitmap* pOldBmp = memDC.SelectObject(&memBmp);

		{
			memDC.FillSolidRect(CRect(rc.left, rc.top, rc.left + rc.Width() / 2, rc.bottom), RGB(255, 255, 0));
			CPoint c(rc.left + rc.Width() / 4, rc.top + rc.Height() / 2);
			int r = rc.Width() / 4 - 10 * 2;
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
			CBrush brs(RGB(255, 0, 0));
			CPen* pOldPen = memDC.SelectObject(&pen);
			CBrush* pOldBrs = memDC.SelectObject(&brs);
			memDC.Pie(CRect(c.x - r, c.y - r, c.x + r, c.y + r), CPoint(c.x + r * ::cos(rot + div), c.y + r * ::sin(rot + div)), CPoint(c.x + r * ::cos(rot), c.y + r * ::sin(rot)));
			memDC.SelectObject(pOldPen);
			memDC.SelectObject(pOldBrs);
			pen.DeleteObject();
			brs.DeleteObject();
		}

		pDC->BitBlt(rc.left, rc.top, rc.Width() / 2, rc.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBmp);
		memDC.DeleteDC();
		memBmp.DeleteObject();

		{
			pDC->FillSolidRect(CRect(rc.left + rc.Width() / 2, rc.top, rc.right, rc.bottom), RGB(0, 255, 255));
			CPoint c(rc.left + rc.Width() / 2 + rc.Width() / 4, rc.top + rc.Height() / 2);
			int r = rc.Width() / 4 - 10 * 2;
			CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
			CBrush brs(RGB(0, 0, 255));
			CPen* pOldPen = pDC->SelectObject(&pen);
			CBrush* pOldBrs = pDC->SelectObject(&brs);
			pDC->Pie(CRect(c.x - r, c.y - r, c.x + r, c.y + r), CPoint(c.x + r * ::cos(rot + div), c.y + r * ::sin(rot + div)), CPoint(c.x + r * ::cos(rot), c.y + r * ::sin(rot)));
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrs);
			pen.DeleteObject();
			brs.DeleteObject();
		}

		this->ReleaseDC(pDC);
	}
}

HCURSOR CMfcGdiDoubleBufferingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcGdiDoubleBufferingDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == WM_USER + 0x0001)
	{
		this->Invalidate(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}
