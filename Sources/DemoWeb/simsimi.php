<?php
header("Content-Type: application/json");
header('Access-Control-Allow-Origin: *');
//set_time_limit(0);
/*
Code By Sĩ Ben
Blog: https://www.siblog.net
=> Vui lòng không xóa dòng này ! hãy tôn trọng người viết.
*/
$id_profile = 100004093837273; //ID của nick cần cài sim
$token = 'EAABwzLixnjYBAG16PIah6v2mOq4lIZBPdJ4yZCGxaWLm9GbNKN8F0UyqdXRZCs4aqbtcR0ZAHZAHewAGM6uVwppR2DAm7V4KvsL8kjgd9thVRj8L82ZBy0pPsIbMKzZAWgVnO7jlUUZBV4YtfPtHOAFZALHRYLWnGOyZAyf5EZBZBjZC1z9mqdOFZABkWREfAZCofZBm5P9ijUibCw9bppMYmeeMNDAe&data_access_expiration_time=0'; //Token của nick cần cài sim
$limit = 1; //Chỉ check 5 người nhắn tin đầu tiên trong messenger
$soluong = 5; //Chỉ đọc tối đa 5 tin nhắn của người khác gữi cho mình
$graph = json_decode(file_get_contents('https://graph.facebook.com/v3.2/me/threads?fields=id,link&limit='.$limit.'&access_token='.$token), true);
for($a=0;$a<count($graph['data']);$a++){
$id_cangui = $graph['data'][$a]['link'];
$siben = array("/messages/t/", "/");
$sibendz = str_replace($siben,"",$id_cangui);
$id_mess = $graph['data'][$a]['id'];
$message = json_decode(file_get_contents('https://graph.facebook.com/'.$id_mess.'/messages?fields=from,to,message,id&limit='.$soluong.'&access_token='.$token), true);
for($b=0;$b<count($message['data']);$b++){
$check = $message['data'][$b]['from']['id'];
$id_nguoigui = $message['data'][$b]['from']['id'];
if($check != $id_profile){
$message_nguoigui = $message['data'][$b]['message'];
//api simsimi có thể thay đổi nhé
$apisim = json_decode(file_get_contents('http://fb.siblog.net/api/simsimi.php?key=sibendz&text='.urlencode($message_nguoigui)), true);
$text = $apisim['messages'][0]['text'];
if(!$text){
$text = 'Tôi không hiểu bạn đang nói gì !';
}
$text .= "\nBot #simsimi - Anh Tuấn";
//api gữi tin nhắn của Facebook
SendCode($sibendz,urlencode($text),$token);
echo "đã gữi: ".$sibendz."\n";
}else{
echo "false\n";
break;
}
}
}
function SendCode($idfb,$message,$token){
$app = app($token);
$appid = $app['id'];
$cookie = get_cookie('https://api.facebook.com/method/auth.getSessionforApp?access_token='.$token.'&format=json&new_app_id='.$appid.'&generate_session_cookies=1');
if($idfb && $message && $cookie && $token){
$url = curl("https://mbasic.facebook.com/messages/read/?fbid=".$idfb,$cookie);
if(preg_match('#name="jazoest" value="(.+?)"#is',$url, $_siben))
{
$jazoest = $_siben[1];
}
if(preg_match('#name="fb_dtsg" value="(.+?)"#is',$url, $_siben))
{
$fb_dtsg = $_siben[1];
}
if(preg_match('#name="tids" value="(.+?)"#is',$url, $_siben))
{
$tids = $_siben[1];
}
if(preg_match('#name="csid" value="(.+?)"#is',$url, $_siben))
{
$csid = $_siben[1];
}
$test = post_data("https://mbasic.facebook.com/messages/send/?icm=1&refid=12","fb_dtsg=".$fb_dtsg."&jazoest=".$jazoest."&body=".$message."&send=G%E1%BB%ADi&tids=".$tids."&wwwupp=C3&ids%5B".$idfb."%5D=".$idfb."&referrer=&ctype=&cver=legacy&csid=".$csid,$cookie);
}else{
die('xảy ra lỗi.');
}
}
function app($a = NULL){
if($a){
$result = file_get_contents('https://graph.facebook.com/app?access_token='.$a);
return json_decode($result, true);
}
else return false;
}
function get_cookie($a){
$cookie_nguon = file_get_contents($a);
$c_user = tach($cookie_nguon, 'c_user","value":"', '"');
$datr = tach($cookie_nguon, 'datr","value":"', '"');
$fr = tach($cookie_nguon, '"fr","value":"', '"');
$xs = tach($cookie_nguon, '"xs","value":"', '"');
$cookie = 'c_user='.$c_user.'; xs='.$xs.'; fr='.$fr.'; datr='.$datr.'';
return $cookie;
}
function tach($noidung, $start, $stop) {
$bd = strpos($noidung, $start);
$tru = strlen($start);
$bd = $bd + $tru;
$noidungg = substr($noidung, $bd);
$kt = strpos($noidungg, $stop);
$content = substr($noidungg, 0, $kt);
return $content;
}
function post_data($site,$data,$cookie){
$datapost = curl_init();
$headers = array("Expect:");
curl_setopt($datapost, CURLOPT_URL, $site);
curl_setopt($datapost, CURLOPT_TIMEOUT, 40000);
curl_setopt($datapost, CURLOPT_HEADER, TRUE);
curl_setopt($datapost, CURLOPT_HTTPHEADER, $headers);
curl_setopt($datapost, CURLOPT_USERAGENT, 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/37.0.2062.124 Safari/537.36');
curl_setopt($datapost, CURLOPT_POST, TRUE);
curl_setopt($datapost, CURLOPT_POSTFIELDS, $data);
curl_setopt($datapost, CURLOPT_COOKIE,$cookie);
ob_start();
return curl_exec($datapost);
ob_end_clean();
curl_close ($datapost);
unset($datapost); 
}
function curl($url,$cookie)
{
$ch = @curl_init();
curl_setopt($ch, CURLOPT_URL, $url);
$head[] = "Connection: keep-alive";
$head[] = "Keep-Alive: 300";
$head[] = "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7";
$head[] = "Accept-Language: en-us,en;q=0.5";
curl_setopt($ch, CURLOPT_USERAGENT, 'Opera/9.80 (Windows NT 6.0) Presto/2.12.388 Version/12.14');
curl_setopt($ch, CURLOPT_ENCODING, '');
curl_setopt($ch, CURLOPT_COOKIE, $cookie);
curl_setopt($ch, CURLOPT_HTTPHEADER, $head);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
curl_setopt($ch, CURLOPT_TIMEOUT, 60);
curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 60);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
curl_setopt($ch, CURLOPT_HTTPHEADER, array(
'Expect:'
));
$page = curl_exec($ch);
curl_close($ch);
return $page;
}
?>