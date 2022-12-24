# Pokedex
## חלק א'
ניצור מערכת המאפשרת ביצוע קרבות פוקימונים, אשר יכיל מידע על הפוקימנים וסוגי פוקימונים קיימים.
בניית פוקדקס, יתמקד בכתיבת הפוקימונים הסוגים השונים וביצוע פעולות עליהם, תוך דגש על הגדרת structs, יצירת מצביעים, הקצאות ושחרור זיכרון ועוד.
החלק השני יצירת קרבות בין פוקימוניםת יתמקד בבנית ADT גנרי.
הראשון – בניית ה pokedex , יתמקד בכתיבת הפוקימונים
והסוגים השונים וביצוע פעולות עליהם, תוך דגש על הגדרת structs , יצירת מצביעים,
הקצאות ושחרור זיכרון ועוד.
החלק השני )שיפורט בתרגיל 3 ( יצירת קרבות בין פוקימונים, יתמקד בבניית ADT גנרי.
תתבקשו ליצור ADT גנרי לפי הדרישות, שאינו תלוי בשימוש שייעשה בו בהמשך. בנוסף
יהיה עליכם להשתמש בממשק ה- ADT כדי ליצור את מערכת הקרבות שתפורט בעבודה
הבאה.
אנא לפני תחילת פתירת התרגיל קראו עד הסוף את העבודה על מנת למנוע אי הבנות.

דוח עבודה##  PokemonsBattles
 
![image](https://user-images.githubusercontent.com/62882347/209447509-fe20302a-e4e8-463a-a6ea-21e5d5b53d29.png)

בעבודה ישנם 3 מודלים:
#### MaxHeap
אחריות הערימה להחזיק את האלמנטים ( הפוקימונים) ומאפשרת בגישה של O(1)  לקבל את האיבר המקסימלי
תחום האחריות של הערימה מתבטא במטודת ה-fight כאשר מתבקש להביא עבור כל סוג פוקימון את הפוקימון עם המתקפה הגבוהה ביותר ובכך בוחרים את הפוקימון החזק ביותר מהמערכת המתאים לקרב מכל הסוגים שקיימים
בזמן של O(types) = O(1)
LinkedList
אחריות הרשימה המקושרת לקשר את כל הערימות על פי סדר הכנסתן, מאפשר הגדלה והקטנה של הרשימה בכך שמוסיפים או מורידים סוגים מסויימים.
מאפשר במעבר אחיד לעבור על הרשימה המקושרת ולבדוק עבור כל ערימה את הפוקימון החזק ביותר עבור הסוג
כמו שפורט קודם.

#### BattleByCategory
אחריות מערכת הקרב על פי סוג, להחזיק מבנה נתונים רשימה מקושרת שכל איבר בו הוא ערימת מקסימום
מאפשר ניהול של הקרבות ומחבר בין כל הערימות בעזרת מטודות כמו למשל getAttackFunction
המעניק למשתמש את היכולת להעביר פונקציה לפי רצונו שתשווה בין פוקימונים שונים הקיימים במערכת
ועל פי הסוג של הערימה תוסיף ותוריד כוח בהתאם לחולשות והחוזקות של הסוגים.


התמודדות הקצאה דינמית לאורך כל המודולים קיימת עקביות של מעקב status מלטה עד למעלה,
למשל ביצירת BattleByCategory:
נבדוק אם ביצירת רשימה מקושרת קיבלו כישלון, אחרת נוסיף ערימות לרשימה המקושרת, אם בהוספה של ערימה לרשימה מקושרת (יצירת node חדש) קיבלנו כישלון או מעצם יצירת הערימה קיבלנו כישלון, יוחזר למערכת הקרב כישלון שכמו כן ישלך למשתמש ב- MainSecond.c משם למשתמש יש את האפשרות להתמודד אם התקלה כרצונו.
על כל הקצאת זיכרון הקיימת במודולים היית בדיקה ומכך ישלח null\failure  במעלה ההירכיה עד שתגיע אל המשתמש.
בדוגמא ניתן לראות שקיימת הקצאת זיכרון בהדפסת הערימה, כישלון כלומר לא היה מקום להקצות לעותק
לכן הרשימה המקושרת תקבל כישלון מפוקנציית ההדפסה של הערימה, ותחזיר כישלון גם כן.

 ![image](https://user-images.githubusercontent.com/62882347/209447558-5c1c5c64-8e48-4918-bada-39f1332dbfc1.png)



#### ADT 
MaxHeap
 ![image](https://user-images.githubusercontent.com/62882347/209447560-942bde4d-a574-4557-aa2f-d5dcfc7bcb13.png)

בקובץ ה-header מופיעים כל המטודות שיהיו שימושיות למשתמש, במקרה הזה עבור BattleByCategory
בקובץ לא מופיעות כלל המטודות המשמשות לניהול הערימה כמו כן מבנה הערימה אינו חשוף למשתמש בקובץ h
מכיוון שאין שום צורך בכך, משתמשים בדרך יחידה שהיא הוספה, מחיקה, הריסה, הדפסה, פופמקס, טופמקס
נמנע מהמשתמש לראות את ניהול הערימה כגון UpHeapify, DownHeapify
כמו כן מערך הערימה אינו חלק, שינוי או הוספה של אלמנט למקום במערך בצורה ידנית עלול לפגוע בכל מבנה הערימה ולהוביל לתקלות, חוסר עקביות בניהול הערימה, דבר שנרצה למנוע.




ה-struct  יושב בקובץ ה-source השדותמוסתרים מהמשתמש 
למנוע עריכה או שינוישל שדות בצורה ידנית עלולים לפגוע
 במימוש\מאזן הערימה ולהוביל לתקלות וקריסת קוד.
למשל הוספת איבר הגודל מהמקסימלי לסוף הערימה יפגע בתכונות
הערימה.
Int size, maxSize בגודל 4 בייטים, בסך הכל 8 בייטים.
4 function pointers 16 בייטים, בסך הכל 64 בייטים.
Char* בגודל 8 בייטים.
בנוסף גודל :Node
מצביע מסוג void* אל אלמנט בגודל 8 בייטים.
Index int 4 בייטים. סך הכל גודל node 12 בייטים.
בחזרה לערימה: מערך של מצביעים אל Nodes גודל המערך יהיה כגודל ה-Capacity הנתון מראש
לכן גודלו של כל תא Node* + Node = 20
גודל המערך heap: 20*Capacity  כאשר הערימה מלאה. 
סה"כ: 80 + 20*capacity 
כל השדות של הערימה נמצאים בשימוש לאורך כל התוכנה, אפשר לדון על גודל מערך ה-heap שהוא קבוע מראש
וגודלו הוא המקסימלי, אבל מצד שני יצירה של מערך גדל וקטן (realloc) לדעתי היה פחות יעיל ומגושם.
![image](https://user-images.githubusercontent.com/62882347/209447544-4cacd7a1-8f91-4ea2-831f-0487cfa21a65.png)



#### CreateHeap פונקציית יצירת   
![image](https://user-images.githubusercontent.com/62882347/209447571-e83d0561-91e3-47a7-8b47-da199adbd0db.png)
![image](https://user-images.githubusercontent.com/62882347/209447573-f80d6afa-16ab-4353-b023-052a8125529a.png)

#### LinkedList
מבנה הרשימה מקושרת יושב בקובץ ה-source על מנת למנוע
עריכה לא מבוקרת של המבנה הוא של אלמנטים הקיימים במבנה הנתונים.
בכל המטודות בקובץ ה-header  קיים שימוש
במערכת הקרבות שמימשנו המאפשר פעולות על
או בעזרת הרשימה המקושרת למציאת ערכים רצויים
על פי תנאים.
![image](https://user-images.githubusercontent.com/62882347/209447575-c24a9736-3b36-434c-bfbb-5e60d2dac4f1.png)

![image](https://user-images.githubusercontent.com/62882347/209447577-695bde00-f841-4760-9d06-34d3275987ef.png)

![image](https://user-images.githubusercontent.com/62882347/209447581-533a527f-c751-4d24-996f-01fcf9d5ec4b.png)

![image](https://user-images.githubusercontent.com/62882347/209447583-46d550fc-414e-49d9-92b2-2bdd994c7ab0.png)

גודל Node:
מצביע אל 2  Nodes , גודל כל מצביע 8, בסך הכל 16.
מצביע אל element מסוג void* בגודל 8 . סך הכל גודל node  24.
גודל LinkedList
4 function pointers בגודל 16 בייטים כל אחד, סך הכל 64 בייטים.
Int size בגודל 8.
מצביע אל 2 Nodes head, tail בגודל 8 בייטים כל אחד, סך הכל 16 בייטים.
לסיכום גודל רשימה מקושרת 102 בייטים.
כל השדות נמצאים בשימוש לארוך התוכנה וגודלה קבוע. לכן הרשימה חסכונית.
  

#### BattleByCategory
![image](https://user-images.githubusercontent.com/62882347/209447645-a16d689c-bfab-4033-bb4b-758adabee6da.png)

 
3 מצביעים מסוג פונקציה בגודל 16 בייטים , בסך הכל 48 בייטים.
Int מספר קטגוריות 8 בייטים.
רשימה מקושרת בגודל 102 בייטים.
סה"כ: 158 בייטים

<img width="129" alt="image" src="https://user-images.githubusercontent.com/62882347/209447660-f96a59fc-6887-47b2-a120-bcbe8ad438fc.png">

מצביע ממערכת הקרבות אל הרשימה מקושרת.
שימוש ברשימה מקושרת השומרת על סדר הכנסת הסוגים למערכת.
 המחזיקה מצביעים אל ערימות המקסימום שכל ערימה היא סוג של פוקימונים
וכל אלמנט בערימה הוא פוקימון.

![image](https://user-images.githubusercontent.com/62882347/209447683-e72badfc-d2c3-4189-bfec-bbfc62ffe7a9.png)


במעבר על הרשימה המוקצרת, תתבצע בדיקה עבור כל סוג
שהוא ערימת מקסימום, אם הפוקימון הנמצא בראש לאחר החלת האפקטים
המתאימים ל-2 הסוגים המשתתפים, בבדיקה של ההפרש הקודם
שהתקבל בפונקציית getAttack
יוחלט אם הפוקימון הנוכחי מהמערכת
חזק ממש מהפוקימון הקודם 
שנבחר במערכת, במעבר על כל הסוגים מצאנו את הפוקימון
המתאים ביותר לקרב ונבחר בו לנהל את הקרב מול פוקימון הניתן.
![image](https://user-images.githubusercontent.com/62882347/209447687-1427e34f-b033-49f6-866c-5780f4b17d7b.png)

#### Pokemon
הוספתי פונקציה נוספת, שימשה בלבד להוספת פוקימון למערכת דרך הממשק, 
המימוש היה שונה לכן הייתי צריך ליצור פונקציה גמישה יותר בנוסף ליצירת פוקימונים בדרך אחרת
 ![image](https://user-images.githubusercontent.com/62882347/209447693-b157d81c-9e52-427d-a3a7-e5745649378f.png)


### Main
האובייקטים בקובץ המיין נוצרו כמו בעבודה 1.
יצרתי Pokedex בשלמותו, מכיוון שבהכנסת פוקימונים אל מערכת הקרב משתמשים בפונקציית העתקה,
לכן שחררתי את כל הפוקימונים ברגע הוספתם ואת כל המידע הרלוונטי אליהם.
לאחר תהליך זה נשארתי עם Pokedex השומר על כל הסוגים והאפקטים הקיימים במערכת.
כמו כן מתבצע מעקב אחרי כמות הפוקימונים מכל סוג בפוקדקס וכמו כן בערימות המקסימום הרלוונטיות.
![image](https://user-images.githubusercontent.com/62882347/209447753-2efbaecd-12d3-470e-bd6e-e32a883c409a.png)

בקריאת הקובץ 
השתמשתי בהקצאת זיכרון עבור כל השורות הנקראות מהקובץ ובעזרת פיצול שהוסבר בעבודה 1
שמרתי את כל המידע הרלוונטי עבור כל אובייקט על פי השורות המתקבלות מהקובץ בצורה ישירה.
בשחרור כל השורות של הקובץ בעצם אני משחרר את כל המידע הרלוונטי שהפוקדקס יחזיק.
לא הצלחתי להימנע מכמות מידע אדוקה מכיוון שכמות השורות אינה ניתנת אז בעזרת הערכה גסה
של כל השורות הקצתי מקום והתחלתי לקרוא עד הגעה לסוף הקובץ. 
קובץ Main אינו מחולק לתתי פונקציות מלבד פונקציית הקריה שכתובה בנפרד מטעמי אסתטיות.
בנוסף בקובץ יש את המטודות הרלוונטיות לעבודה זו שצריך להעביר אל כל מבנה נתונים מסוג ADT 

![image](https://user-images.githubusercontent.com/62882347/209447700-86d4655a-f021-4873-ab06-eeb5b8793638.png)

כמו כן בקבלת פוקימון להוספה למשתמש כתבתי תת פונקציה, במבט לאחור זו דרך מעט מגושמת אבל היה בה היגיון בעת הכתיבה. אחראית על קריאה רציפה של קלטים מהמשתמש לסטרינג אחד המוקצה בזיכרון,
לאחר מכן שליחה של הסטרינג אל יצירת הפוקימון שיודע לפצל על פי dilemeter והשמה לשדות המתאימים של הפוקימון.
 
 ![image](https://user-images.githubusercontent.com/62882347/209447716-07eb9497-0c7a-4f2e-9933-4fe6c645ef57.png)

![image](https://user-images.githubusercontent.com/62882347/209447725-6708fe66-cdb2-4b2c-8b14-1cafe11fa483.png)


סיכום ###
חושב שההפרדה הלוגית היא סבירה בגלל שכל מה שמופיע בקובץ Main נקבע על פי הקובץ הנתון שנקרא
פונקציות העתקה, מחיקה, הוספה קבועות לכן כתיבה שלהן בקובץ Pokemon.c אם הכי הרבה היגיון מכיוון
שהן לא תלויות במודל אלה במודל הפוקימון.
מלבד זאת התוכנה אמורה לרוץ אם כל מודל בהינתן פונקציות ADT הנדרשות לכל ADT 
וכתיבת קריאת קובץ אחרת בהתאם לניתן, לא יפגע במטרות התוכנה.





דו"ח עבודה מספר ##  C Pokemons
Pokemon.c- במודל הזה מתבצע כל תהליכי הטעינה
1)	קריאה מקובץ 
2)	טעינה של פרטי הקובץ ל-structs המצויניים למטה
3)	קיימים מימושים עבור הדפסות הוספת אפקטים במודל הזה
Pokemon.h- תחום אחריות של קובץ זה לקשר בין MainFirst.c ל-Pokemon.c
		בקובץ ה-MainFirst אנו מקבלים את כל האינפוטים מהמשתמש
		מנתיב קובץ הקונפיגירציה, מספר פוקימונים, מספר סוגים
		עד קבלת אינפוטים בתפריט המשתמש.
		כל האינפוטים הללו נשלחים לקובץ Pokemon.c המבצע את הפקודה
		על מבנה ה-Pokedex ומחזיר\מבצע שינוי\מוחק\מוסיף לפי הפקודה 			שהוכנסה.
MainFirst.c- ממשק המשתמש, מתקבל בו תחילה הנתיב לקובץ,מספר הפוקימונים
		מספר הסוגים. לאחר טעינה מוצלחת של Pokedex ינתן למשתמש 
		תפריט המקבל קלטים ובהתאם לכך מבצע את המטודות הממושות
		ב-Pokemons.c
Defs.h- משמש בעיקר להדפסת תקלות חוזרות
	e_status, e_bool הועברו לקובץ Pokemon.h מטעמי קומפליציה.
 

![image](https://user-images.githubusercontent.com/62882347/209447262-91921936-d8fd-47e7-a6cc-18d846b7bb8d.png)


כל ה-structs בקוד נכתבו ב-Pokemon.h מהסיבה שיש שימוש בכל struct
גם ב-Pokemon.c MainFirst.c

הסבר: זה המידע על הפוקימון
יכיל רק את גודל המשתנים הפרימטיביים הנתונים. 
מהסטרינג ממנו אני מלקט את המידע ישחורר 
בסוף התוכנית.
גודלו יהיה: 
		Integer attack -גודל 4
		Float weight-גודל 8
		Float Height-גודל 8  
הסבר: מבנה זה בנוי מפוינטרים בלבד לכן
גודלו יהיה 4*sizeof(pointer)
כל שדותיו מצביעים על זיכרון מוקצה בצורה 
אופטימלית, למשל Pickachu אז name יצביע על
זיכרון מוקצה בגודל 9. ניהול המידע המלא יוסבר בקריאה מהקובץ.
בסה"כ גודלו יהיה בערך 32.
![image](https://user-images.githubusercontent.com/62882347/209447279-5908f1c4-083c-4d74-a4c0-53c69bd66b51.png)

הסבר: name לפי ההסבר למעלה ויוסבר בהמשך
	מצביע בגודל 8.
	Pokemons- מערך של מצביעים לפוקימונים
	גודולו המקסימלי יהיה num_of_pokemons*sizeof(pokemon*)
	Effective_me\other מנוהלים בצורה זהה לפוקימונים. גודלם המקסימלי יהיה
	Num_of_types*sizeof(Type*).


![image](https://user-images.githubusercontent.com/62882347/209447284-7d26aece-0c70-4145-a494-eb84643c757c.png)



הסבר: Pokedex מכיל את הגישה לכל האובייקטים הקיימים
בקוד, רוב המטודות משתמשות בו על מנת לגשת למקום
הרצוי וביצוע פעולו בהתאם.
גודלו יהיה בגודל קבוע של 
Num_of_pokemons*sizeof(pokemon*)
Num_of_types*size(types*)
2 integers
Num_of_pokemons, num_of_types 
משמש לדעת כמה פוקימונים ישלנו במהלך הטעינה
משמש בעיקר אם נתקלתי בתקלה של טעינת הפוקימונים שנוכל לצאת מהתוכנית בצורה מסודרת ככל האפשר, שחרור כמות האובייקטים במערך זה לעת זו. 
אם במידה באיטרציה I תקלה
בהקצאת זיכרון,
Pokedex->num_of_types=i-1
לכן unload_pokedex(pokedex)
ישחרר בצורה נכונה את הטייפס הנמצאים.
![image](https://user-images.githubusercontent.com/62882347/209447292-077a1bd0-00fe-4bec-b1b3-93cc5f7bc89d.png)

החסכוניות שמימוש הזה נובעת מכך שכל המבנים מלבד Bio בנויים על ints
ומצביעים מסוג מסוים. כל המצביעים הקיימים מצביעים על אותו אובייקט בקוד
כך שלא נוצרים עותקים של אובייקטים כלל בקוד. בדרך זו כל אובייקט שנוצר 
למשל pickachu בכל מקום אליו מתאים יצביעו לאובייקט יחיד מסוגו

![image](https://user-images.githubusercontent.com/62882347/209447301-2babed81-3b5e-4008-b5cb-798e0e701ae0.png)

לדוגמא :
 ![image](https://user-images.githubusercontent.com/62882347/209447304-f3158bc1-6f05-41cd-9d5e-f911d5f75a8c.png)

בקטע קוד זה למשל 
Pokemon->name = Pikachu;
Type->name = Electric;
אז ניצור מצביע חדש במערך הפוקימונים של Electric אשר יצביע לאובייקט Pikachu
הקיים במערכת, כמו כן 
Pikachu->type = (Type) Electric
ביצעתי הצבעה הדדית בין האובייקטים כך של קיים עותק מלבד המצביעים.
מכאן ניתן לראות שכל המבנים המבוססים על מצביעים בקוד ישתמשו באובייקטים הקיימים שנוצרו פעם אחת במשך כל התוכנית.

יצירת הפוקימון סטנדרטית, בהינתן המידע נבצע השמה של השדות הדרושים,
שדה type ישאר לא מאותחל, יאותחל מבחוץ בעזרת פוקנציית assigen 
המצורפת הנ"ל.

 ![image](https://user-images.githubusercontent.com/62882347/209447313-dc498e19-2113-48d9-91e8-b96256b46c37.png)

הריסת פוקימון:
![image](https://user-images.githubusercontent.com/62882347/209447316-020ddd6b-71f1-4953-bfb7-f3cb77aa6abd.png)

אני משחרר עבור כל פוקימון במערך pokedex->pokemons
עבור כל פוקימון משחרר את אובייקט Bio_Info אשר לשדות שלו לא הוקצה זיכרון לכן שחרור האובייקט לבד פעולה מספקת. 
	שחרור כל אובייקט של פוקימון.
	שחרור כל pokemon->type יתבצע בעזרת unload_types
	יתר השדות ישוחרר ב- Unload_pokedex..
![image](https://user-images.githubusercontent.com/62882347/209447342-ce4c3a4f-5fc9-4631-9217-99f5d3d2cbc8.png)


מקבלים את השורה הרלוונטית str (שורה 2 בקובץ) אשר אליה הוקצה זיכרון בקריאת הקובץ ויוסבר בהמשך. מבצעים הקצאות זיכרון רלוונטיות למערך המצביעים שיהיה
שייך ל-pokedex->types . עבור כל תא נקצה זיכרון למצביע מסוג (Type*)
וכל מצביע אל אובייקט (Type). השמה של השדות הרלוונטים. 
כרגע 0 פוקימונים השייכים לאובייקט, בהמשך בעזרת פוקנציית assigen_pokemon
נעדכן בהתאם. מערכי האפקטים יהיו מצביע המצביע ל-NULL מטעמי מימוש.


![image](https://user-images.githubusercontent.com/62882347/209447345-30ea3a74-ffc3-4654-a229-b4a697e17842.png)

הריסת הסוג: הריסת מערך הפוקמונים הריק, כל הפוקימונים שוחררו בטרם עת בעזרת פונקציית unload_Pokemons שהוזכרה קודם.
שחרור מערכי האפקטים, אין צורך לשחרר את התאים מפני ששורה לאחר מכן
ישחורר הסוג, בגלל מצביעים הדדים בכל התוכנית.  כל הסוגים ישוחררו אז
כל רשימות האפקטים בתוכנית ישוחררו בצורה מסודרת. לכן רק שחרור מערכי המצביעים של האפקטים מספקת.
לבסוף שחרור types השייך ל- pokedex->types.
 ![image](https://user-images.githubusercontent.com/62882347/209447368-ec32bfdd-7e69-43c8-91d9-8cd8981c7899.png)

יצירת האובייקט Pokedex* , השמה של כל השדות לערכי ברירת מחדל.
לאחר מכן בעזרת הפונקציות שהוצגו קודם נתאחל את כל השדות.
פונקציית load_effect תטען את כל האפקטים לשדות מערכי האפקטים בסוגים.


קודם אסביר על מטודה שלדעתי היא הלב של כל התוכנית, slice_str
בקבלת char* שהיא גם שורה בקובץ הקונפגירציה, בהתאם לצורך
נפריד את כל המילים בשורה הזו בעזרת strtok והשמה של מצביע
עבור כל תחילת מילה הבאה אחרי ה-delimeter ציור c_tutor.
![image](https://user-images.githubusercontent.com/62882347/209447383-6abb4696-35d5-4f80-a333-440731ea3ad9.png)

![image](https://user-images.githubusercontent.com/62882347/209447385-dcaf07d6-cbbd-4b08-9508-1b0cdee26cf9.png)

במקרה המתואר כל מצביע ישמש את לבנות את כל המצביעים ב- pokedex->types[i]
כל המצביעים נבנים על זיכרון שכבר הוקצה בתחילת התוכנית.
לכן שחרור buffer. הנעשה ב-unload_pokedex ישחרר את כל הערכים שהתאים מצביעים אליהם. לכן שחרור רק המצביע יהיה מספיק ב-unload_types.
![image](https://user-images.githubusercontent.com/62882347/209447387-7b11a6ec-c5ad-4804-a3b5-99cd92e36a5c.png)


Load_effect
![image](https://user-images.githubusercontent.com/62882347/209447392-5d22657e-704b-40a6-86be-20231d070e5e.png)

 כאן ניתן לראות שימוש מלא של slice_str בטעינת האפקטים מקובץ הקונפיגרציה
אינפוט לדוגמא:
Fire effective-against-other:Grass,Ice
צריך לפרק את האינפוט הנ"ל לפי 3 סוגים של delimeters
ופירוק של הסוגים לפי delimeter =’,’
במימוש שהשימוש בסטרינגים הנתונים הינו לחיפוש ומציאה של אובייקטים קיימים במערכת כמו (Type) Grass לכן אשחרר את כל המצביעים שהוחזרו מהתוכנית.
קיים הסבר לפונקציית typeA_effect_typeB בקובץ Pokemon.h.
דוגמת קוד להרחבה 

דוגמאות קוד שהקצאה דינמית לא הצליחה:

![image](https://user-images.githubusercontent.com/62882347/209447394-5734773f-27f2-4c67-a055-adc1f0ba293f.png)

 ![image](https://user-images.githubusercontent.com/62882347/209447396-86046ca1-bf75-4956-9f7a-702977dede51.png)

![image](https://user-images.githubusercontent.com/62882347/209447397-0d758aaa-8abc-46c8-ba8f-222f0f4d1ff3.png)

![image](https://user-images.githubusercontent.com/62882347/209447398-d0e11b60-b2b5-4956-865d-104c043d6ba9.png)

![image](https://user-images.githubusercontent.com/62882347/209447400-4a66f826-7c4a-4a27-80c3-f17bb255a754.png)

![image](https://user-images.githubusercontent.com/62882347/209447402-c0752098-0450-44ef-9b94-a5441362924a.png)

![image](https://user-images.githubusercontent.com/62882347/209447403-c894d5b1-bdad-464c-baed-ed196651a2dc.png)

![image](https://user-images.githubusercontent.com/62882347/209447405-e130fcdf-3ed5-4458-87f9-ff0dc09a48bf.png)

![image](https://user-images.githubusercontent.com/62882347/209447408-ba31361f-9963-477c-b5d2-a080a65f572f.png)

![image](https://user-images.githubusercontent.com/62882347/209447414-93459236-ba98-403a-b260-22f524eae097.png)

![image](https://user-images.githubusercontent.com/62882347/209447418-0fdbf6e1-175b-4c33-bc46-0d3cb20f2941.png)



מחיקה הוספה של פוקימונים מרשימה :
![image](https://user-images.githubusercontent.com/62882347/209447428-c79baa75-6ea2-42a7-be53-685712a3b3f1.png)

מערך האפקטים שלי בנוי כך שבסוף כל מערך קיים ערך null
כך ניתן לעבור על המערך ולספור את כמו האובייקטים הקיימים בו,
בעזרת realloc והגודל הנתון נבנה מערך הגדול ב-1 או קטן ב-1 מהקודם.
וכמובן השמה של ערך NULL. בסוף המערך החדש לפעולות עתידיות נוספות.
כאשר הרשימה ריקה, יהיה מצביע ל-NULL שישמש בהדפסות עתידיות.
בקבלת רשימת האפקטים בהוספה מקבלים את המצביע לסוג ומצביע לרשימת האפקטים, כולם שייכים ל-pokedex
Pokedex->types = effects
Pokedex->types[i](toAdd) = type;
כך בהגדלת המערך המצביע האחרון יצביע לטייפ הקיים, כך נמנע שוב מעותקים ונשתמש באובייקטים קיימים והעברתם בעזרת מצביעים.
המחיקה משחררת את המצביע הדרוש, לא נשחרר את המקום אליו מצביע כי זהו סוג הקיים במבנה נתונים אשר ישוחרר בתום התוכנית.
קריאת הקובץ
אצלי בתכנית הקריאה מהקובץ התבצע בתוך הקובץ Pokemon.c
מהסיבה העיקרית ששמירת כל השורות במערך מצביעים char* המחזיק
מצביעים לכל הזיכרונות שהוקצו עבור כל תוכנית במערכת.
כל שורה במערכת תשמש עבור שדות האובייקטים. כך בקריאה אחת מהקובץ נקצה את כל הזיכרון הנדרש עבור כל char* שקיים במבנה הנתונים, דבר שיאפשר גם שחרור קל של רוב הזיכרון שהוקצה במערכת.
באמצעות חישוב חמדן חישבתי את כמות השורות המקסימלית שיכולה להיות,
כנראה שיכולתי לחסוך על כמות השורות בריצה ראשוניית על הקובץ וספירת כל השורות ולאחר מכן להקצות את כמות השורות הדרושה. 
כל הפעולות יבוצעו על ידי slice_str, וכמו שהוסבר קודם לא יקוצה זיכרון נוסף מעבר לנדרש.
(מבדיקה שעשיתי יצא כי דרך זו יצאה יקרה יותר, לפי החישוב כנראה שיש סוג רב של טייפים השיטה המוצעת היא המועדפת, אך לא למקרה של fullrun_data).
 ![image](https://user-images.githubusercontent.com/62882347/209447449-39541c76-844e-4757-a5fc-60ad846d641f.png)
 ![image](https://user-images.githubusercontent.com/62882347/209447451-c754e719-5f52-4848-9787-b7401bfe956a.png)
![Uploading image.png…]()


 
במידה וישנו את קובץ ה-main
לא יובצע שינוי בתוכנית כלל. הדבר הכרחי לכך שהתוכנית תעבוד כראוי זה 
נתינת הארגומנטים התקינים (נתיב קובץ קונפגירציה תקין, מספר פוקימונים, מספר סוגים). כך התוכנית תטען את המבנה נתונים בצורה תקינה תמיד.
שינוי קובץ ה-Main ישנה את הפקודות שניתנות לקובץ הפוקימונים, דרישותיו יענו בקובץ ה Pokemon.h ובמידת הצורך ימוששו מטודות על מבנה הנתונים הקיים של הפוקימונים בקובץ Pokemon.c. 

בהרצת התוכנית עם valgrind  ישנה תקלה שלא הצלחתי לתקן של uncondtional jump, מבדיקות שעשיתי אינה פוגעת ברצף התוכנית או בדליפות הזיכרון.











