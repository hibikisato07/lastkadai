//
//  main.cpp
//  lastkadai
//
//  Created by 佐藤響 on 2024/07/22.
//
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <set>
#include <unordered_set>
using namespace std;

//Flightクラスを定義、フライト情報を保持
class Flight {
public:
    string destination;  //目的地
    int requiredMiles;   //必要となるマイル数
    string connectingAirport;  //乗り換え空港

    //コンストラクタ
    Flight(const string& dest, int miles, const string& connect = "")
        : destination(dest), requiredMiles(miles), connectingAirport(connect) {}
};


//JALCardクラス
class JALCard {
protected:
    string type;
    int milesPerYen;
public:
    JALCard(const string& cardType, int milesPerYenSpent)
        : type(cardType), milesPerYen(milesPerYenSpent) {}

    virtual ~JALCard() {}

    virtual int calculateRequiredYen(int requiredMiles) = 0;
    virtual int adjustMiles(int requiredMiles) = 0;
};


class JALNaviCard : public JALCard {
public:
    JALNaviCard() : JALCard("JALNavi", 1) {}

    int calculateRequiredYen(int requiredMiles) override {
        return requiredMiles * 100;
    }
    
    int adjustMiles(int requiredMiles) override {
        return requiredMiles / 2; // 必要マイル数を半分にする
    }
};

class JALStandardCard : public JALCard {
public:
    JALStandardCard() : JALCard("JALStandard", 0.5) {}

    int calculateRequiredYen(int requiredMiles) override {
        return requiredMiles * 200;
    }
    
    int adjustMiles(int requiredMiles) override {
        return requiredMiles;
    }
};

void printDestinations(const vector<Flight>& flights, const vector<Flight>& connectingFlights, const string& departure) {
    map<string, set<string>> regions = {
        {"北海道", {"函館(HKD)", "奥尻(OIR)", "札幌(SPK)", "利尻(RIS)", "女満別(MMB)", "根室中標津(SHB)", "釧路(KUH)", "旭川(AKJ)", "帯広(OBO)"}},
        {"東北", {"青森(AOJ)", "三沢(MSJ)", "秋田(AXT)", "花巻(HNA)", "仙台(SDJ)", "山形(GAJ)"}},
        {"関東", {"東京(TYO)"}},
        {"中部", {"松本(MMJ)", "静岡(FSZ)", "名古屋(NGO)", "小松(KMW)", "新潟(KIJ)"}},
        {"近畿", {"大阪(OSA)", "南紀白浜(SHM)", "但馬(TJH)"}},
        {"中国", {"出雲(IZO)", "岡山(OKJ)", "広島(HIJ)", "山口宇部(UBJ)", "隠岐(OKI)"}},
        {"四国", {"徳島(TKS)", "高松(TAK)", "高知(KCZ)", "松山(MYJ)"}},
        {"九州", {"福岡(FUK)", "北九州(KKJ)", "五島福江(FUJ)", "対馬(TSJ)", "長崎(NGS)", "壱岐(IKI)", "熊本(KMJ)", "天草(AXJ)", "大分(OIT)", "宮崎(KMI)", "鹿児島(KOJ)", "種子島(TNE)", "屋久島(KUM)", "喜界島(KKX)", "奄美大島(ASJ)", "徳之島(TKN)", "沖永良部(OKE)", "与論(RNJ)"}},
        {"沖縄", {"沖縄（那覇）(OKA)", "久米島(UEO)", "宮古(MMY)", "与那国(OGN)", "石垣(ISG)", "北大東(KTD)", "南大東(MMD)"}},
    };

    unordered_set<string> uniqueDestinations;
    for (const auto& flight : flights) {
        uniqueDestinations.insert(flight.destination);
    }
    for (const auto& flight : connectingFlights) {
        uniqueDestinations.insert(flight.destination);
    }

    for (const auto& region : regions) {
        vector<string> destList;
        for (const auto& dest : uniqueDestinations) {
            if (region.second.find(dest) != region.second.end() && dest != departure) {
                destList.push_back(dest);
            }
        }
        if (!destList.empty()) {
            cout << region.first << ":\n";
            for (const auto& dest : destList) {
                cout << "  - " << dest << "\n";
            }
        }
    }
}

int main() {
    map<string, vector<Flight>> flights = {
        {"札幌(SPK)", {{"函館(HKD)", 4000}, {"奥尻(OIR)", 4000}, {"利尻(RIS)", 5000}, {"女満別(MMB)", 5000}, {"根室中標津(SHB)", 5000},
                   {"釧路(KUH)", 5000}, {"青森(AOJ)", 5000}, {"三沢(MSJ)", 5000}, {"秋田(AXT)", 6000}, {"花巻(HNA)", 6000},
                   {"仙台(SDJ)", 7000}, {"山形(GAJ)", 7000}, {"新潟(KIJ)", 7000}, {"松本(MMJ)", 8000}, {"静岡(FSZ)", 8000},
                   {"出雲(IZO)", 8000}, {"徳島(TKS)", 8000}, {"東京(TYO)", 8000}, {"大阪(OSA)", 8000}, {"名古屋(NGO)", 8000},
                   {"広島(HIJ)", 9000}, {"福岡(FUK)", 9000}}},
        {"東京(TYO)", {{"仙台(SDJ)", 5000}, {"山形(GAJ)", 5000}, {"新潟(KIJ)", 5000}, {"名古屋(NGO)", 5000}, {"秋田(AXT)", 6000},
                  {"花巻(HNA)", 6000}, {"小松(KMW)", 6000}, {"大阪(OSA)", 6000}, {"函館(HKD)", 7000}, {"青森(AOJ)", 7000},
                  {"三沢(MSJ)", 7000}, {"南紀白浜(SHM)", 7000}, {"岡山(OKJ)", 7000}, {"出雲(IZO)", 7000}, {"広島(HIJ)", 7000},
                  {"徳島(TKS)", 7000}, {"高松(TAK)", 7000}, {"高知(KCZ)", 7000}, {"松山(MYJ)", 7000}, {"大分(OIT)", 7000},
                  {"札幌(SPK)", 8000}, {"女満別(MMB)", 8000}, {"旭川(AKJ)", 8000}, {"釧路(KUH)", 8000}, {"帯広(OBO)", 8000},
                  {"山口宇部(UBJ)", 8000}, {"福岡(FUK)", 8000}, {"北九州(KKJ)", 8000}, {"長崎(NGS)", 8000}, {"熊本(KMJ)", 8000},
                  {"宮崎(KMI)", 8000}, {"鹿児島(KOJ)", 8000}, {"奄美大島(ASJ)", 9000}, {"沖縄（那覇）(OKA)", 9000},
                  {"久米島(UEO)", 10000}, {"宮古(MMY)", 10000}, {"石垣(ISG)", 10000}}},
        {"名古屋(NGO)", {{"東京(TYO)", 5000},{"新潟(KIJ)", 6000},{"出雲(IZO)", 6000}, {"高知(KCZ)", 6000}, {"青森(AOJ)", 7000},
                  {"花巻(HNA)", 7000},{"山形(GAJ)", 7000}, {"福岡(FUK)", 7000}, {"熊本(KMJ)", 7000}, {"帯広(OBO)", 8000},
                  {"釧路(KUH)", 8000},{"札幌(SPK)", 8000}, {"沖縄（那覇）(OKA)", 9000},{"宮古(MMY)", 10000}, {"石垣(ISG)", 10000}}},
        {"大阪(OSA)", {{"但馬(TJH)", 4000}, {"高知(KCZ)", 4000}, {"松本(MMJ)", 5000}, {"隠岐(OKI)", 5000}, {"出雲(IZO)", 5000},
                  {"松山(MYJ)", 5000}, {"福岡(FUK)", 6000}, {"熊本(KMJ)", 6000}, {"宮崎(KMI)", 6000},{"東京(TYO)", 6000},
                  {"秋田(AXT)", 7000}, {"花巻(HNA)", 7000}, {"仙台(SDJ)", 7000}, {"山形(GAJ)", 7000}, {"新潟(KIJ)", 7000},
                  {"長崎(NGS)", 7000},{"鹿児島(KOJ)", 7000}, {"種子島(TNE)", 7000}, {"屋久島(KUM)", 7000}, {"札幌(SPK)", 8000},
                  {"旭川(AKJ)", 8000},{"函館(HKD)", 8000}, {"青森(AOJ)", 8000}, {"三沢(MSJ)", 8000}, {"奄美大島(ASJ)", 8000},
                  {"徳之島(TKN)", 8000},{"沖縄（那覇）(OKA)", 8000},{"女満別(MMB)", 9000}, {"宮古(MMY)", 9000}, {"石垣(ISG)", 9000}}},
        {"福岡(FUK)", {{"松山(MYJ)", 4000}, {"対馬(TSJ)", 4000}, {"五島福江(FUJ)", 4000}, {"天草(AXJ)", 4000}, {"宮崎(KMI)", 4000},
                  {"鹿児島(KOJ)", 4000}, {"出雲(IZO)", 5000}, {"高知(KCZ)", 5000}, {"徳島(TKS)", 6000}, {"屋久島(KUM)", 6000},
                  {"大阪(OSA)", 6000},{"松本(MMJ)", 7000}, {"静岡(FSZ)", 7000}, {"奄美大島(ASJ)", 7000}, {"花巻(HNA)", 8000},
                  {"仙台(SDJ)", 8000}, {"東京(TYO)", 8000},{"新潟(KIJ)", 8000}, {"沖縄（那覇）(OKA)", 8000}, {"札幌(SPK)", 9000}}},
        {"鹿児島(KOJ)", {{"種子島(TNE)", 4000}, {"屋久島(KUM)", 4000}, {"福岡(FUK)", 4000}, {"喜界島(KKX)", 6000}, {"奄美大島(ASJ)", 6000},
                  {"徳之島(TKN)", 6000},{"沖永良部(OKE)", 7000}, {"与論(RNJ)", 7000}, {"大阪(OSA)", 7000}, {"松本(MMJ)", 8000},
                  {"静岡(FSZ)", 8000},{"出雲(IZO)", 8000},{"徳島(TKS)", 8000},  {"東京(TYO)", 8000}, {"広島(HIJ)", 9000}}},
        {"沖縄（那覇）(OKA)", {{"沖永良部(OKE)", 4000}, {"与論(RNJ)", 4000}, {"久米島(UEO)", 4000}, {"奄美大島(ASJ)", 5000}, {"宮古(MMY)", 5000},
                  {"石垣(ISG)", 6000}, {"北大東(KTD)", 6000}, {"南大東(MMD)", 6000}, {"与那国(OGN)", 7000}, {"岡山(OKJ)", 8000},
                  {"福岡(FUK)", 8000}, {"大阪(OSA)", 8000}, {"東京(TYO)", 9000}, {"名古屋(NGO)", 9000}, {"小松(KMW)", 9000}, {"広島(HIJ)", 9000}}},

    };

    map<string, vector<Flight>> connectingFlights = {
        {"東京(TYO)", {{"但馬(TJH)", 7000, "大阪(OSA)"}, {"隠岐(OKI)", 8000, "大阪(OSA)or出雲(IZO)"},
                  {"対馬(TSJ)", 8000, "福岡(FUK)or長崎(NGS)"},{"五島福江(FUJ)", 8000, "福岡(FUK)or長崎(NGS)"},
                  {"壱岐(IKI)", 8000, "長崎(NGS)"}, {"天草(AXJ)", 8000, "福岡(FUK)or熊本(KMJ)"},
                  {"種子島(TNE)", 8000, "鹿児島(KOJ)"}, {"屋久島(KUM)", 8000, "大阪(OSA)or福岡(FUK)or鹿児島(KOJ)"},
                  {"喜界島(KKX)", 8000, "鹿児島(KOJ)or奄美大島(ASJ)"},{"徳之島(TKN)", 9000, "鹿児島(KOJ)or奄美大島(ASJ)"},
                  {"沖永良部(OKE)", 9000, "鹿児島(KOJ)or沖縄（那覇）(OKA)"},
                  {"与論(RNJ)", 9000, "鹿児島(KOJ)or沖縄（那覇）(OKA)"},{"与那国(OGN)", 10000, "沖縄（那覇）(OKA)or石垣(ISG)"}}}
    };
    
    map<string, string> airportShortcuts = {
        {"AKJ", "旭川(AKJ)"}, {"HKD", "函館(HKD)"}, {"KUH", "釧路(KUH)"}, {"MMB", "女満別(MMB)"},{"OBO", "帯広(OBO)"},
        {"OIR", "奥尻(OIR)"}, {"SPK", "札幌(SPK)"}, {"AOJ", "青森(AOJ)"},{"AXT", "秋田(AXT)"}, {"GAJ", "山形(GAJ)"},
        {"HNA", "花巻(HNA)"}, {"MSJ", "三沢(MSJ)"},{"SDJ", "仙台(SDJ)"}, {"KIJ", "新潟(KIJ)"}, {"MMJ", "松本(MMJ)"},
        {"TYO", "東京(TYO)"},{"NGO", "名古屋(NGO)"}, {"KMW", "小松(KMW)"}, {"OSA", "大阪(OSA)"}, {"SHM", "南紀白浜(SHM)"},
        {"TJH", "但馬(TJH)"}, {"HIJ", "広島(HIJ)"}, {"IZO", "出雲(IZO)"}, {"OKI", "隠岐(OKI)"},{"OKJ", "岡山(OKJ)"},
        {"UBJ", "山口宇部(UBJ)"}, {"KCZ", "高知(KCZ)"}, {"MYJ", "松山(MYJ)"},{"TAK", "高松(TAK)"}, {"TKS", "徳島(TKS)"},
        {"FUK", "福岡(FUK)"}, {"KKJ", "北九州(KKJ)"},{"KMI", "宮崎(KMI)"}, {"KMJ", "熊本(KMJ)"}, {"KOJ", "鹿児島(KOJ)"},
        {"NGS", "長崎(NGS)"},{"OIT", "大分(OIT)"}, {"ASJ", "奄美大島(ASJ)"}, {"KKX", "喜界島(KKX)"}, {"KUM", "屋久島(KUM)"},
        {"OKE", "沖永良部(OKE)"}, {"RNJ", "与論(RNJ)"}, {"TKN", "徳之島(TKN)"}, {"TNE", "種子島(TNE)"},{"ISG", "石垣(ISG)"},
        {"MMY", "宮古(MMY)"}, {"OGN", "与那国(OGN)"}, {"OKA", "沖縄（那覇）(OKA)"},{"UEO", "久米島(UEO)"}, {"FUJ", "五島福江(FUJ)"},
        {"TSJ", "対馬(TSJ)"}, {"AXJ", "天草(AXJ)"}, {"IKI", "壱岐(IKI)"}, {"RIS", "利尻(RIS)"}, {"FSZ", "静岡(FSZ)"},
        {"SHB", "根室中標津(SHB)"}, {"KTD", "北大東(KTD)"}, {"MMD", "南大東(MMD)"}
    };

    string cardType, departure, destination;
    int currentMiles;
    char roundTrip;

    cout << "JALカードの種類を入力してください（JALNavi(N)またはJAL普通カード(S)）：";
    cin >> cardType;
    cout << "現在のマイル数を入力してください：";
    cin >> currentMiles;
    cout << "出発地を入力してください（札幌(SPK)、東京(TYO)、名古屋(NGO)、大阪(OSA)、福岡(FUK)、鹿児島(KOJ)、沖縄（那覇）(OKA)）：";
    cin >> departure;
    
    // 出発地の略称を変換
    if (airportShortcuts.find(departure) != airportShortcuts.end()) {
        departure = airportShortcuts[departure];
    } else {
        cout << "無効な出発地が入力されました。" << endl;
        return 1;
    }

    // 出発地から行ける目的地のリストを表示
    cout << departure << "から行ける目的地は以下の通りです：" << endl;
    if (flights.find(departure) != flights.end()) {
        printDestinations(flights[departure], connectingFlights[departure], departure);
    } else {
        cout << "該当する出発地が見つかりません。" << endl;
        return 1;
    }

    cout << "行きたい場所を入力してください：";
    cin >> destination;
    
    // 目的地の略称を変換
    if (airportShortcuts.find(destination) != airportShortcuts.end()) {
        destination = airportShortcuts[destination];
    } else {
        cout << "無効な目的地が入力されました。" << endl;
        return 1;
    }
    
    cout << "片道（O）または往復（R）を選択してください：";
    cin >> roundTrip;

    JALCard* card;
    if (cardType == "N") {
            card = new JALNaviCard();
        } else if (cardType == "S") {
            card = new JALStandardCard();
        } else {
            cout << "無効なカード種類が入力されました。" << endl;
            return 1;
        }

    bool found = false;
    for (auto it = flights[departure].begin(); it != flights[departure].end(); ++it) {
        if (it->destination == destination) {
            found = true;
            int adjustedMiles = card->adjustMiles(it->requiredMiles);
            int neededMiles = adjustedMiles * (roundTrip == 'R' ? 2 : 1) - currentMiles;
            if (neededMiles < 0) neededMiles = 0;

            int requiredYen = card->calculateRequiredYen(neededMiles);
            cout << "目的地: " << destination << "\n"
                      <<  destination <<"までのマイル数（片道）: " << adjustedMiles << "\n"
                      << destination <<"までのマイル数（往復）: " << adjustedMiles * 2 << "\n"
                      << "必要となるマイル数（-:不足，+:充足）: " << currentMiles - adjustedMiles * (roundTrip == 'R' ? 2 : 1) << "マイル\n"
                      << "使用しないといけない金額: " << requiredYen << "円\n";
  //          if (!it->connectingAirport.empty()) {
   //             cout << "目的地には" << it->connectingAirport <<"空港での乗り換えが必要です\n";
  //          }
            break;
        }
    }

    if (!found && connectingFlights.find(departure) != connectingFlights.end()) {
        for (auto it = connectingFlights[departure].begin(); it != connectingFlights[departure].end(); ++it) {
            if (it->destination == destination) {
                found = true;
                int adjustedMiles = card->adjustMiles(it->requiredMiles);
                int neededMiles = adjustedMiles * (roundTrip == 'R' ? 2 : 1) - currentMiles;
                if (neededMiles < 0) neededMiles = 0;

                int requiredYen = card->calculateRequiredYen(neededMiles);
                cout << "目的地: " << destination << "\n"
                          << destination <<"までのマイル数（片道）: " << adjustedMiles << "\n"
                          << destination <<"までのマイル数（往復）: " << adjustedMiles * 2 << "\n"
                          << "必要となるマイル数（-:不足，+:充足）: " << currentMiles - adjustedMiles * (roundTrip == 'R' ? 2 : 1) <<"マイル\n"
                          << "使用しないといけない金額: " << requiredYen << "円\n";
                if (!it->connectingAirport.empty()) {
                    cout << "目的地には" << it->connectingAirport <<"空港での乗り換えが必要です\n";
                }
                break;
            }
        }
    }

    if (!found) {
        cout << "該当する目的地が見つかりません。\n";
    }

    delete card;
    return 0;
}
