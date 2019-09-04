<?php


if (isset($_GET['number']) && isset($_GET['message'])) {
    $number=$_GET['number'];
    $message=$_GET['message'];
    $curl = curl_init();

curl_setopt_array($curl, array(
  CURLOPT_URL => "https://api.sms.to/v1/oauth/token",
  CURLOPT_RETURNTRANSFER => true,
  CURLOPT_ENCODING => "",
  CURLOPT_MAXREDIRS => 10,
  CURLOPT_TIMEOUT => 0,
  CURLOPT_FOLLOWLOCATION => false,
  CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
  CURLOPT_CUSTOMREQUEST => "POST",
  CURLOPT_POSTFIELDS =>'{"grant_type": "password","client_id": "your clined id","client_secret": "your secret","username": "your user name","password": "your password","scope": "*"}',
  CURLOPT_HTTPHEADER => array(
    "Content-Type: application/json",
    "Accept: application/json"
  ),
));

$response = curl_exec($curl);
$someArray = json_decode($response, true);
$token=$someArray['access_token'];
//print_r($someArray['access_token']);
$err = curl_error($curl);
//print_r($response);
curl_close($curl);

$curl = curl_init();

curl_setopt_array($curl, array(
  CURLOPT_URL => "https://api.sms.to/v1/sms/single/send",
  CURLOPT_RETURNTRANSFER => true,
  CURLOPT_ENCODING => "",
  CURLOPT_MAXREDIRS => 10,
  CURLOPT_TIMEOUT => 0,
  CURLOPT_FOLLOWLOCATION => false,
  CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
  CURLOPT_CUSTOMREQUEST => "POST",
  CURLOPT_POSTFIELDS =>'{"messages":[{"to":"+'.$number.'", "message": "'.$message.'"}],"sender_id":"kiosk"}',
  CURLOPT_HTTPHEADER => array(
    "Authorization: Bearer $token",
    "Accept: application/json",
    "Content-Type: application/json"
  ),
));

$response = curl_exec($curl);
$err = curl_error($curl);
print_r($response);
curl_close($curl);
}



