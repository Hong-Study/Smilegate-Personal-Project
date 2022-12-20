# Smilegate-Personal-Project
스마일게이트 개인 프로젝트 GitHub 입니다.
# URLShortener Application

## 서비스 개요
|서비스|개요|
|---|---|
|URL Shortner|- URLLong 입력시 ShortUrl 출력<br>- 생성된 ShortUrl을 통해서 원래 url 접속 가능<br>- 생성된 URLShort를 DB에 저장|


## 기술스택
- C++ 14
- MFC
- Mysql 8.xx
- Docker
- Github

## 아키텍처
- 초기 아키텍처
![image](Smilegate-Personal-Project/img/캡처.PNG)

- 수정 아키텍처

## 제공 기능
- URL Mapping : 짧아진 도메인 주소를 본래의 긴 주소로 치환해서 응답해주는 기능
- Key Generation : 짧은 식별자를 생성하여 긴 URL을 짧은 URL을 생성해주는 기능
- Cleanup : 데이터베이스를 주기적으로 Cleaning 해주는 기능
- Load Balancer(Rate Limiter) : DBMS 모든 URL 매핑 요청마다 매핑 정보를 담당하면 부하가 걸리기에 요청량 조절하는 기능 -> MHA DB 설계
- App에서 복사하기 클릭 시 클립보드로 자동 복사 기능
- URL 입력 시 해당 URL 웹사이트 열어주는 기능
- 본래는 ShortURL을 입력하면 원래 페이지로 응답해줘야 하나, 특성상 힘들기 때문에, ShortURL을 입력하고 브라우저 버튼 클릭시, 원래 URL이 출력되고 그 URL로 브라우저가 열림.
