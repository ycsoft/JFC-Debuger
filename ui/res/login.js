
// JavaScript Document
function caMouseIn(obj)
{
	obj.style.backgroundColor = "#FF8040";	
	tips(obj.id,"ʹ��CA֤���¼�����������û�������");
}
function caMouseOut(obj)
{
	outtips();
	obj.style.backgroundColor = "#CDCDCD";
}


function tips(id,str){

    t= getTop(document.getElementById(id))-document.getElementById(id).offsetHeight;

    l=  getLeft(document.getElementById(id));

    document.getElementById("tips").innerHTML="��ʾ��"+str;

    document.getElementById("tips").style.left=l+"px";

    document.getElementById("tips").style.top=t+"px";

    document.getElementById("tips").style.display="";

}

function outtips(){

    document.getElementById("tips").style.display='none';

}

//��ȡԪ�ص�������

    function getTop(e){

        var offset=e.offsetTop;

        if(e.offsetParent!=null) offset+=getTop(e.offsetParent);

        return offset;

    }

    //��ȡԪ�صĺ�����

    function getLeft(e){

        var offset=e.offsetLeft;

        if(e.offsetParent!=null) offset+=getLeft(e.offsetParent);

        return offset;

    }