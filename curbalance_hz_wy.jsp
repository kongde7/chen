
<%@page import="java.math.BigDecimal"%>
<%@page import="weaver.hrm.company.SubCompanyComInfo"%>
<%@page import="weaver.hrm.resource.ResourceComInfo"%>
<%@page import="weaver.conn.RecordSet"%>
<%@page import="weaver.general.Util"%>
<%@page language="java" contentType="text/html; charset=UTF-8" %>
<%@page import="weaver.hrm.User"%>
<%@page import="weaver.hrm.HrmUserVarify"%>
<%@ include file="/hrm/header.jsp" %>
<%@page import="weaver.interfaces.ebu2.Ebu2Util"%>
<%
String imagefilename = "/images/hdReport_wev8.gif";
String titlename = "计划额度汇总表" ;
String needfav ="1";
String needhelp ="";
/*获得URL中参数数值*/
// String condition="";
// String fromDate = request.getParameter("fromDate")==null?"":request.getParameter("fromDate");
// String toDate = request.getParameter("toDate")==null?"":request.getParameter("toDate");
// String sjndCon = request.getParameter("sjndCon")==null?"":request.getParameter("sjndCon");
// String sjlxCon = request.getParameter("sjlxCon")==null?"":request.getParameter("sjlxCon");
// String bsjdwCon = request.getParameter("bsjdwCon")==null?"":request.getParameter("bsjdwCon");
// String sjfzr = request.getParameter("sjfzr")==null?"":request.getParameter("sjfzr");
// if(!fromDate.equals("")){
// 	condition += " and kssj >= '"+fromDate+"' ";
// }
// if(!toDate.equals("")){
// 	condition += " and jssj <= '"+toDate+"' ";
// }
// if(!sjndCon.equals("")){
// 	condition += " and sjnd = '"+sjndCon+"' ";
// }
// if(!sjlxCon.equals("")){
// 	condition += " and sjzxlx = '"+sjlxCon+"' ";
// }
// if(!bsjdwCon.equals("")){
// 	condition += " and bsdw = '"+bsjdwCon+"' ";
// }
// if(!sjfzr.equals("")){
// 	condition += " and bsjdwfzr = '"+sjfzr+"' ";
// }
// request.setAttribute("condition",condition);
// ResourceComInfo rci = new ResourceComInfo();
// SubCompanyComInfo sci = new SubCompanyComInfo();
// String sjndnameCon = getSjnd(sjndCon);
// String sjlxnameCon = getSjlx(sjlxCon);
// String bsjdwnameCon = sci.getSubcompanyname(bsjdwCon);
// String sjfzrname = rci.getLastname(sjfzr);
%>

<html>
	<head>
		<link href="/css/Weaver_wev8.css" type="text/css" rel="STYLESHEET">
		<link href="/workplan/calendar/css/calendar_wev8.css" rel="stylesheet" type="text/css" /> 
		<link href="/workplan/calendar/css/dp_wev8.css" rel="stylesheet" type="text/css" />   
		<link href="/workplan/calendar/css/main_wev8.css" rel="stylesheet" type="text/css" /> 
		<script type="text/javascript" src="/js/weaver_wev8.js"></script>
		<script type="text/javascript" src="/appres/hrm/js/mfcommon_wev8.js"></script>
		<script type="text/javascript" defer="defer" src="/js/datetime_wev8.js"></script>
		<script type="text/javascript" defer="defer" src="/js/JSDateTime/My97DatePicker/WdatePicker.js"></script>
		<script src="/meeting/calendar/src/Plugins/jquery.datepickernew_wev8.js" type="text/javascript"></script>
		<script src="/meeting/calendar/src/Plugins/datepicker_lang_ZH_wev8.js" type="text/javascript"></script> 
		<script src="/meeting/calendar/src/Plugins/wdCalendar_lang_ZH_wev8.js" type="text/javascript"></script>  
		<LINK REL=stylesheet type=text/css HREF=/css/Weaver_wev8.css></HEAD>
<link rel="stylesheet" href="/css/ecology8/request/requestTopMenu_wev8.css" type="text/css" />
<link rel="stylesheet" href="/wui/theme/ecology8/jquery/js/zDialog_e8_wev8.css" type="text/css" />
<link type="text/css" rel="stylesheet" href="/css/Weaver_wev8.css">
<link type="text/css" rel="stylesheet" href="/appres/hrm/css/mfcommon_wev8.css">
<script type="text/javascript" src="/interface/propage/js/jquery-1.12.0.min.js"></script>
<!-- 时间控件 -->
<SCRIPT language="javascript" src="/js/datetime_wev8.js"></script>
<SCRIPT language="javascript" src="/js/JSDateTime/WdatePicker_wev8.js"></script>
<style type="text/css">
		table.altrowstable {font-family: verdana,arial,sans-serif;font-size:11px;color:#333333;border-width: 1px;border-color: #E6E6E6;border-collapse: collapse;}
		table.altrowstable th {
			border-width: 1px;
			padding: 8px;
			border-style: solid;
			border-color: #E6E6E6;
		}
		table.altrowstable td {
			border-width: 1px;
			padding: 8px;
			border-style: solid;
			border-color: #E6E6E6;
			border-style: solid;
		}

		.selected {
			background-color: #F0FBEA!important;
		}
		.mout{
		   border-top:0px #f7f7f7 solid;
		   width:0px;
		   height:0px;
		   border-left:80px #f7f7f7 solid;
		   position:relative;
		}
		mf{font-style:normal;display:block;position:absolute;border:1;top:-10px;left:-10px;width:35px;}
		mem{font-style:normal;display:block;position:absolute;border:1;top:0px;left:-80px;width:55x;}
		
		.page { width: 100%; margin: auto;}
        .listtable { margin-top: 10px;}
        .listtable table {border: none;border-collapse: collapse;width: 100%;white-space: nowrap; table-layout:fixed;}
        .listtable table .head tr { color: #333;background-color: #f7fbfe;border-bottom: 1px solid #e2ecf2;border-bottom-width: 2px;overflow: hidden;white-space: nowrap;word-break: break-all;text-overflow: ellipsis; font-size: 12px; text-align: center;padding:7px 5px; font-weight: normal; }
        .listtable table td { position: relative; border-bottom: 1px solid #e2e2e2; font-size: 12px; text-align: center;padding:7px 5px; white-space:normal;word-break:break-all;overflow: auto;}
		.listtable table td p{height: 20px; background: #eee;}
		.listtable table td p span {height: 20px;}
		.listtable table td:nth-child(6) p { border-bottom-left-radius: 10px;border-top-left-radius: 10px; }
		.listtable table td:nth-last-child(2) p {  border-bottom-right-radius: 10px;border-top-right-radius: 10px; }
		.listtable table td:nth-child(6) p span { border-bottom-left-radius: 10px;border-top-left-radius: 10px; }
		.listtable table td:nth-last-child(2) p span {  border-bottom-right-radius: 10px;border-top-right-radius: 10px;}
		.active1 p span {border-bottom-right-radius: 10px;border-top-right-radius: 10px;}
		.padzero { padding: 7px 0 !important; }
        .padleft { padding: 7px 0px 7px 5px !important;}

        .padright { padding:7px 5px 7px 0 !important;}
        .padleft span { display: block; height: 12px; border-bottom-left-radius: 5px;border-top-left-radius: 5px;}
        .padzero span { display: block; height: 12px; }
        .padright span { display: block; height: 12px; border-bottom-right-radius: 5px;border-top-right-radius: 5px;}
        .hover span {  !important;}
        /*background: #03a116
        background-color: #03a116;
        */
        /*.active span {  width: 50%;height: 12px;background: #03a116 !important;}*/
        /*.active span::after {content: "";position: absolute;right: 0;top: 15px;border-left: 15px solid #03a116;border-top: 15px solid transparent;border-bottom: 15px solid transparent;}*/
		.jump-ipt{ width:10%;}
<%--        .active1 span { position: relative; margin-right: 20px;}--%>
<%--        .active2 span { position: relative; margin-right: 20px;}--%>
<%--        .active3 span { position: relative; margin-right: 20px;}--%>
<%--        .active1 span:after {content: ' ';height: 0;width: 0;border: 15px solid  transparent;border-left-color: blue;position: absolute;top: -75%;right: -20px;}--%>
<%--        .active2 span:after {content: ' ';height: 0;width: 0;border: 15px solid  transparent;border-left-color: red;position: absolute;top: -75%;right: -20px;}--%>
<%--        .active3 span:after {content: ' ';height: 0;width: 0;border: 15px solid  transparent;border-left-color: #03a116;position: absolute;top: -75%;right: -20px;}--%>
<%--		--%>
	</style>
	</head>
<body >
	<%@ include file = "/systeminfo/TopTitle_wev8.jsp" %>
	<%@ include file="/systeminfo/RightClickMenuConent_wev8.jsp" %>
	<%
	RCMenu += "{搜索,javascript:showResult(),_self} " ;
	RCMenuHeight += RCMenuHeightStep ;
	
	%>	
	<%@ include file="/systeminfo/RightClickMenu_wev8.jsp" %>
	<table border="0" class=ViewForm>
		<tr>
			<td align="left" style="width: 43px;"><img src="/js/tabs/images/nav/mnav12_wev8.png"/></td>
			<td align="left"  ><h2>计划额度汇总表</h2></td>
			<td align="right" style="padding-right: 10px;"></td>
		</tr>
		<TR class=Spacing><TD class=Line colSpan=3></TD></TR>
	</table>
	<input type="hidden" name="isself" value="1">
	<%--暂时不做分页 20210402--%>
	<jsp:include   page="pageList.jsp" >
        <jsp:param value="2" name="pageSize"/> <!-- 每页条数 -->
        <jsp:param value="xmbh"  name="prikey"/> <!-- 主键  -->
        <jsp:param value="类型,计划额度(单位:万元),减:本月新增逾期(单位:万元),加:本月前增量逾期还款(单位:万元),实际可放款(单位:万元),审批中(单位:万元),对接中(单位:万元),已放款(单位:万元),合计(单位:万元),余额(单位:万元)"  name="columns"/>
        <jsp:param value=""  name="fields"/><!-- 数据库字段 -->
        <jsp:param value=""  name="tablenames"/><!-- 表名，或者查询主体 -->
        <jsp:param value="" name="otherparms"/> <!-- 打开页面其他传入参数 -->
        <jsp:param value ="id"  name="order" /> <!-- 排序字段-->
        <jsp:param value =""  name="url" /> <!-- 跳转页面地址-->
    </jsp:include>
	<%
		String count = request.getAttribute("count")+"";
		String pageSize = request.getAttribute("pageSize")+"";
		String[] colArr = (String[])request.getAttribute("colArr");
		RecordSet rs11 = (RecordSet)request.getAttribute("rs");
		RecordSet rst = new RecordSet();

		Calendar today = Calendar.getInstance();
		String yearmonth = Util.add0(today.get(Calendar.YEAR), 4) + "-" + Util.add0(today.get(Calendar.MONTH) + 1, 2);
		//out.print("当前年月："+yearmonth);

		String ckzed = "0.00"; //敞口总额度
		String ldzed = "0.00"; //流贷总额度
		String ckyed = "0.00"; //敞口原额度
		String ldyed = "0.00"; //流贷原额度
		String ckyced = "0.00"; //敞口隐藏额度
		String ldyced = "0.00"; //流贷隐藏额度
		String ckbyxzyq = "0.00"; //敞口本月新增逾期
		String ldbyxzyq = "0.00"; //流贷本月新增逾期
		String ckbyqyqhk = "0.00"; //敞口本月前逾期还款
		String ldbyqyqhk = "0.00"; //流贷本月前逾期还款
		String ckspz_157 = "0.00"; //敞口-审批中-资金预算申请表
		String ldspz_157 = "0.00"; //流贷-审批中-资金预算申请表
		String ckspz_198 = "0.00"; //敞口-审批中-采购计划申请表
		String ldspz_198 = "0.00"; //流贷-审批中-采购计划申请表
		String ckdjz_157 = "0.00"; //敞口-对接中-资金预算申请表
		String lddjz_157 = "0.00"; //流贷-对接中-资金预算申请表
		String ckdjz_198 = "0.00"; //敞口-对接中-采购计划申请表
		String lddjz_198 = "0.00"; //流贷-对接中-采购计划申请表
		String ckyfk_157 = "0.00"; //敞口-归档-资金预算申请表
		String ldyfk_157 = "0.00"; //流贷-归档-资金预算申请表
		String ckyfk_198 = "0.00"; //敞口-归档-采购计划申请表
		String ldyfk_198 = "0.00"; //流贷-归档-采购计划申请表

		String sql_uf_zed = "select sum(ckzed) as ckzed, " +
				"sum(ldzed) as ldzed, " +
				"sum(ckyed) as ckyed, " +
				"sum(ldyed) as ldyed, " +
				"sum(ckyced) as ckyced, " +
				"sum(ldyced) as ldyced, " +
				"sum(ckbyxzyq) as ckbyxzyq, " +
				"sum(ldbyxzyq) as ldbyxzyq, " +
				"sum(ckbyqyqhk) as ckbyqyqhk, " +
				"sum(ldbyqyqhk) as ldbyqyqhk " +
				"from uf_zed where month like '" + yearmonth + "%'";

		// 待删除，已不用
		// String sql_formtable_main_198_first = "select sum(a.ysje) as ysje from formtable_main_198 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (";
		// String sql_formtable_main_198_last = ") and a.sqsj like '" + yearmonth + "%'";
		// String sql_formtable_main_157_first = "select sum(a.jkje) as jkje from formtable_main_157 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (";
		// String sql_formtable_main_157_last = ") and a.sqsj like '" + yearmonth + "%'";

		// 更改字段，采购流程的审批中金额为ysje1，两条流程的对接中为ydjje，已放款都为kfked 20210406
		String sql_formtable_main_157_spz = "select sum(a.jkje) as jkje from formtable_main_157 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (2348,2350,2351,2352,2353,2354,2355,2406) and a.sqsj like '" + yearmonth + "%'";
		String sql_formtable_main_198_spz = "select sum(a.ysje1) as ysje1 from formtable_main_198 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (2357,2359,2360,2361,2362,2363,2364,2718) and a.sqsj like '" + yearmonth + "%'";
		String sql_formtable_main_157_djz = "select sum(a.ydjje) as ydjje from formtable_main_157 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (2366) and a.sqsj like '" + yearmonth + "%'";
		String sql_formtable_main_198_djz = "select sum(a.ydjje) as ydjje from formtable_main_198 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodeid in (2365) and a.sqsj like '" + yearmonth + "%'";

		String sql_formtable_main_157_yfk = "select sum(a.kfked) as kfked from formtable_main_157 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodetype='3' and a.sqsj like '" + yearmonth + "%'"; //formtable_main_157表属于已放款的节点
		String sql_formtable_main_198_yfk = "select sum(a.kfked) as kfked from formtable_main_198 a,workflow_requestbase b where a.requestid = b.requestid and b.currentnodetype='3' and a.sqsj like '" + yearmonth + "%'"; //formtable_main_198表属于已放款的节点
		// String zjspznodeids = "2348,2350,2351,2352,2353,2354,2355,2406"; //formtable_main_157表属于审批中的节点
		// String cgspznodeids = "2357,2359,2360,2361,2362,2363,2364,2718"; //formtable_main_198表属于审批中的节点
		// String zjdjznodeids = "2366"; //formtable_main_157表属于对接中的节点
		// String cgdjznodeids = "2365"; //formtable_main_198表属于对接中的节点

		//查询uf_zed表
		rs.execute(sql_uf_zed);
		while(rs.next()) {
			ckzed = rs.getString("ckzed").isEmpty() ? "0.00" : rs.getString("ckzed");
			ldzed = rs.getString("ldzed").isEmpty() ? "0.00" : rs.getString("ldzed");
			ckyed = rs.getString("ckyed").isEmpty() ? "0.00" : rs.getString("ckyed");
			ldyed = rs.getString("ldyed").isEmpty() ? "0.00" : rs.getString("ldyed");
			ckyced = rs.getString("ckyced").isEmpty() ? "0.00" : rs.getString("ckyced");
			ldyced = rs.getString("ldyced").isEmpty() ? "0.00" : rs.getString("ldyced");
			ckbyxzyq = rs.getString("ckbyxzyq").isEmpty() ? "0.00" : rs.getString("ckbyxzyq");
			ldbyxzyq = rs.getString("ldbyxzyq").isEmpty() ? "0.00" : rs.getString("ldbyxzyq");
			ckbyqyqhk = rs.getString("ckbyqyqhk").isEmpty() ? "0.00" : rs.getString("ckbyqyqhk");
			ldbyqyqhk = rs.getString("ldbyqyqhk").isEmpty() ? "0.00" : rs.getString("ldbyqyqhk");
		}

		// 查询formtable_main_198表-审批中-敞口
		rs.execute(sql_formtable_main_198_spz + " and a.fkfs='0'"); //fkfs付款方式，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ckspz_198 = rs.getString("ysje1").isEmpty() ? "0.00" : rs.getString("ysje1");
		}
		// out.print("敞口审批中_198表：" + sql_formtable_main_198_spz + " and a.fkfs='0'" + "<br>");

		// 查询formtable_main_198表-审批中-流贷
		rs.execute(sql_formtable_main_198_spz + " and a.fkfs='1'"); //fkfs付款方式，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ldspz_198 = rs.getString("ysje1").isEmpty() ? "0.00" : rs.getString("ysje1");
		}
		// out.print("流贷审批中_198表：" + sql_formtable_main_198_spz + " and a.fkfs='1'" + "<br>");

		// 查询formtable_main_198表-对接中-敞口
		rs.execute(sql_formtable_main_198_djz + " and a.fkfs='0'");
		while(rs.next()) {
			ckdjz_198 = rs.getString("ydjje").isEmpty() ? "0.00" : rs.getString("ydjje"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		}
		// out.print("敞口对接中_198表：" + sql_formtable_main_198_djz + " and a.fkfs='0'" + "<br>");

		//查询formtable_main_198表-对接中-流贷
		rs.execute(sql_formtable_main_198_djz + " and a.fkfs='1'");
		while(rs.next()) {
			lddjz_198 = rs.getString("ydjje").isEmpty() ? "0.00" : rs.getString("ydjje"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		}
		// out.print("流贷对接中_198表：" + sql_formtable_main_198_djz + " and a.fkfs='1'" + "<br>");

		// 查询formtable_main_198表-已放款-敞口
		rs.execute(sql_formtable_main_198_yfk + " and a.fkfs='0'"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ckyfk_198 = rs.getString("kfked").isEmpty() ? "0.00" : rs.getString("kfked");
		}

		// 查询formtable_main_198表-已放款-流贷
		rs.execute(sql_formtable_main_198_yfk + " and a.fkfs='1'"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ldyfk_198 = rs.getString("kfked").isEmpty() ? "0.00" : rs.getString("kfked");
		}

		// 查询formtable_main_157表-审批中-敞口
		rs.execute(sql_formtable_main_157_spz + " and a.zjlx='1'");
		while(rs.next()) {
			ckspz_157 = rs.getString("jkje").isEmpty() ? "0.00" : rs.getString("jkje"); //zjlx资金类型 敞口——1银承，流贷——0借款
		}
		// out.print("敞口审批中_157表：" + sql_formtable_main_157_spz + " and a.zjlx='1'" + "<br>");

		// 查询formtable_main_157表-审批中-流贷
		rs.execute(sql_formtable_main_157_spz + " and a.zjlx='0'");
		while(rs.next()) {
			ldspz_157 = rs.getString("jkje").isEmpty() ? "0.00" : rs.getString("jkje"); //zjlx资金类型 敞口——1银承，流贷——0借款
		}
		// out.print("流贷审批中_157表：" + sql_formtable_main_157_spz + " and a.zjlx='0'" + "<br>");

		// 查询formtable_main_157表-对接中-敞口
		rs.execute(sql_formtable_main_157_djz + " and a.zjlx='1'"); //zjlx资金类型 敞口——1银承，流贷——0借款
		while(rs.next()) {
			ckdjz_157 = rs.getString("ydjje").isEmpty() ? "0.00" : rs.getString("ydjje");
		}
		// out.print("敞口对接中_157表：" + sql_formtable_main_157_djz + " and a.zjlx='1'" + "<br>");

		// 查询formtable_main_157表-对接中-流贷
		rs.execute(sql_formtable_main_157_djz + " and a.zjlx='0'"); //zjlx资金类型 敞口——1银承，流贷——0借款
		while(rs.next()) {
			lddjz_157 = rs.getString("ydjje").isEmpty() ? "0.00" : rs.getString("ydjje");
		}
		// out.print("流贷对接中_157表：" + sql_formtable_main_157_djz + " and a.zjlx='0'" + "<br>");

		// 查询formtable_main_157表-已放款-敞口
		rs.execute(sql_formtable_main_157_yfk + " and a.zjlx='1'"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ckyfk_157 = rs.getString("kfked").isEmpty() ? "0.00" : rs.getString("kfked"); //zjlx资金类型 敞口——1银承，流贷——0借款
		}

		// 查询formtable_main_157表-已放款-流贷
		rs.execute(sql_formtable_main_157_yfk + " and a.zjlx='0'"); //cdlx承兑类型，敞口——0承兑，流贷——1现付
		while(rs.next()) {
			ldyfk_157 = rs.getString("kfked").isEmpty() ? "0.00" : rs.getString("kfked"); //zjlx资金类型 敞口——1银承，流贷——0借款
		}

		ckzed = Ebu2Util.floatDivide(ckzed, "10000", 2);
		ldzed = Ebu2Util.floatDivide(ldzed, "10000", 2);
		String hjzed = Ebu2Util.floatAdd(ckzed, ldzed); //合计总额度
		
		ckyed = Ebu2Util.floatDivide(ckyed, "10000", 2);
		ldyed = Ebu2Util.floatDivide(ldyed, "10000", 2);
		String hjyed = Ebu2Util.floatAdd(ckyed, ldyed); //合计原额度
		
		ckyced = Ebu2Util.floatDivide(ckyced, "10000", 2);
		ldyced = Ebu2Util.floatDivide(ldyced, "10000", 2);
		String hjyced = Ebu2Util.floatAdd(ckyced, ldyced); //合计隐藏额度
		
		ckbyxzyq = Ebu2Util.floatDivide(ckbyxzyq, "10000", 2);
		ldbyxzyq = Ebu2Util.floatDivide(ldbyxzyq, "10000", 2);
		String hjbyxzyq = Ebu2Util.floatAdd(ckbyxzyq, ldbyxzyq); //合计本月新增逾期
		
		ckbyqyqhk = Ebu2Util.floatDivide(ckbyqyqhk, "10000", 2);
		ldbyqyqhk = Ebu2Util.floatDivide(ldbyqyqhk, "10000", 2);
		String hjbyqyqhk = Ebu2Util.floatAdd(ckbyqyqhk, ldbyqyqhk); //合计本月前逾期还款
		
		String cksjkfk = Ebu2Util.floatAdd(ckzed, ckyced); //敞口实际可放款
		String ldsjkfk = Ebu2Util.floatAdd(ldzed, ldyced); //流贷实际可放款
		String hjsjkfk = Ebu2Util.floatAdd(cksjkfk, ldsjkfk); //合计实际可放款
		
		ckspz_157 = Ebu2Util.floatDivide(ckspz_157, "10000", 2);
		ckspz_198 = Ebu2Util.floatDivide(ckspz_198, "10000", 2);
		String ckspz = Ebu2Util.floatAdd(ckspz_157, ckspz_198); //敞口-审批中
		
		ldspz_157 = Ebu2Util.floatDivide(ldspz_157, "10000", 2);
		ldspz_198 = Ebu2Util.floatDivide(ldspz_198, "10000", 2);
		String ldspz = Ebu2Util.floatAdd(ldspz_157, ldspz_198); //流贷-审批中
		String hjspz = Ebu2Util.floatAdd(ckspz, ldspz); //合计-审批中
		
		ckdjz_157 = Ebu2Util.floatDivide(ckdjz_157, "10000", 2);
		ckdjz_198 = Ebu2Util.floatDivide(ckdjz_198, "10000", 2);
		String ckdjz = Ebu2Util.floatAdd(ckdjz_157, ckdjz_198); //敞口-对接中
		
		lddjz_157 = Ebu2Util.floatDivide(lddjz_157, "10000", 2);
		lddjz_198 = Ebu2Util.floatDivide(lddjz_198, "10000", 2);
		String lddjz = Ebu2Util.floatAdd(lddjz_157, lddjz_198); //流贷-对接中
		String hjdjz = Ebu2Util.floatAdd(ckdjz, lddjz); //合计-对接中
		
		ckyfk_157 = Ebu2Util.floatDivide(ckyfk_157, "10000", 2);
		ckyfk_198 = Ebu2Util.floatDivide(ckyfk_198, "10000", 2);
		String ckyfk = Ebu2Util.floatAdd(ckyfk_157, ckyfk_198); //敞口-已放款
		
		ldyfk_157 = Ebu2Util.floatDivide(ldyfk_157, "10000", 2);
		ldyfk_198 = Ebu2Util.floatDivide(ldyfk_198, "10000", 2);
		String ldyfk = Ebu2Util.floatAdd(ldyfk_157, ldyfk_198); //流贷-已放款
		String hjyfk = Ebu2Util.floatAdd(ckyfk, ldyfk); //流贷-已放款
		String cklc = Ebu2Util.floatAdd(Ebu2Util.floatAdd(ckspz, ckdjz), ckyfk); //敞口-流程
		String ldlc = Ebu2Util.floatAdd(Ebu2Util.floatAdd(ldspz, lddjz), ldyfk); //流贷-流程
		String hjlc = Ebu2Util.floatAdd(cklc, ldlc); //合计-流程

		// 余额列更改计算规则，余额=计划额度-本月新增逾期+还款-对接中-已放款 20210408
		String ckye = Ebu2Util.floatSubtract(Ebu2Util.floatSubtract(Ebu2Util.floatAdd(Ebu2Util.floatSubtract(ckyed, ckbyxzyq), ckbyqyqhk), ckdjz), ckyfk); //敞口余额
		String ldye = Ebu2Util.floatSubtract(Ebu2Util.floatSubtract(Ebu2Util.floatAdd(Ebu2Util.floatSubtract(ldyed, ldbyxzyq), ldbyqyqhk), lddjz), ldyfk); //流贷余额
		
// 		ckye = Ebu2Util.floatDivide(ckye, "10000", 2);
// 		ldye = Ebu2Util.floatDivide(ldye, "10000", 2);
		String hjye = Ebu2Util.floatAdd(ckye, ldye); //合计余额

	%>
	<wea:layout type="2col">
			<wea:item attributes="{'isTableList':'true','colspan':'full'}">
	        <div class="page">
	        	<div class="listtable">
					<table id="tableExcel" >
						<tr class="head"style="height: 30px; text-overflow: inherit; white-space: nowrap; word-break: keep-all; overflow: hidden; width: 35px; max-width: 35px; border-right: 1px solid transparent; padding-left: 10px; background-color: rgb(248, 248, 248);">
							<%
			                    for(int i=0;i<colArr.length;i++){
			                %>
			                <td>
			                    <%=colArr[i]%>
			                </td>
			                <%
			                    }
			                %>
						</tr>
						<tr>
							<td >敞口</td>
							<td ><%= ckyed %></td>
							<td ><%= ckbyxzyq %></td>
							<td ><%= ckbyqyqhk %></td>
							<td ><%= cksjkfk %><br>（未终审额度<%= ckyced %>）</td>
							<td ><%= ckspz %></td>
							<td ><%= ckdjz %></td>
							<td ><%= ckyfk %></td>
							<td ><%= cklc %></td>
							<td ><%= ckye %></td>
						</tr>
						<tr>
							<td >流贷</td>
							<td ><%=ldyed%></td>
							<td ><%= ldbyxzyq %></td>
							<td ><%= ldbyqyqhk %></td>
							<td ><%= ldsjkfk %><br>（未终审额度<%= ldyced %>）</td>
							<td ><%= ldspz %></td>
							<td ><%= lddjz %></td>
							<td ><%= ldyfk %></td>
							<td ><%= ldlc %></td>
							<td ><%= ldye %></td>
						</tr>
						<tr>
							<td >合计</td>
							<td ><%= hjyed %></td>
							<td ><%= hjbyxzyq %></td>
							<td ><%= hjbyqyqhk %></td>
							<td ><%= hjsjkfk %><br>（未终审额度<%= hjyced %>）</td>
							<td ><%= hjspz %></td>
							<td ><%= hjdjz %></td>
							<td ><%= hjyfk %></td>
							<td ><%= hjlc %></td>
							<td ><%= hjye %></td>
						</tr>
					</table>
				</div>
			</div>
			</wea:item>
	</wea:layout>
<!-- 	<div class="listPageDiv"> -->
<!-- 		<div class="M-box" style="margin-top: 5px;float: right;"></div> -->
<%-- 		<div style="margin-top: 5px;float: left;"><span class="e8_splitpageinfo" <span class="e8_splitpageinfo" style="font-size:12px;text-align:center;display:block;width: 90px;height: 40px;line-height: 38px;"><%=pageSize%>条/页&nbsp;|&nbsp;共<%=count%>条</span></div> --%>
<!-- 	</div> -->
</body>
</html>
