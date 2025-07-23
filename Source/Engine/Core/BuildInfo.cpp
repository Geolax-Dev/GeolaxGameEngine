#include "BuildInfo.h"

static constexpr GGE::BuildNumberType kMajorBuildVersion = 0;
static constexpr GGE::BuildNumberType kMinorBuildVersion = 0;

namespace GGE::BuildIndexDetails
{
    // Month lookup from the first three characters of __DATE__
    consteval BuildNumberType MonthFromStr(const char* m) {
        return
            m[0] == 'J' && m[1] == 'a' && m[2] == 'n' ? 1u :
            m[0] == 'F' ? 2u :
            m[0] == 'M' && m[1] == 'a' && m[2] == 'r' ? 3u :
            m[0] == 'A' && m[1] == 'p' ? 4u :
            m[0] == 'M' ? 5u :
            m[0] == 'J' && m[1] == 'u' && m[2] == 'n' ? 6u :
            m[0] == 'J' && m[1] == 'u' && m[2] == 'l' ? 7u :
            m[0] == 'A' && m[1] == 'u' ? 8u :
            m[0] == 'S' ? 9u :
            m[0] == 'O' ? 10u :
            m[0] == 'N' ? 11u :
            m[0] == 'D' ? 12u :
            
            /*should never happen*/            
            0u;
    }

    // Count leap days from 2000 up to (but not including) year y
    consteval BuildNumberType LeapDaysSinceMillenium(BuildNumberType y) {
        // years divisible by 4, minus those divisible by 100, plus those divisible by 400
        const BuildNumberType a = (y - 2000u - 1u) / 4u + 1u;
        const BuildNumberType b = (y - 2000u - 1u) / 100u + 1u;
        const BuildNumberType c = (y - 2000u - 1u) / 400u + 1u;
        return a - b + c;
    }

    // Days in each month for a non-leap year
    constexpr BuildNumberType kDays[] = {
        0,  // dummy so months are 1-based
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    consteval BuildNumberType ComputeDays() noexcept
    {
        constexpr char const* d = __DATE__;
        // __DATE__ format is "Mmm dd yyyy"
        const BuildNumberType month = MonthFromStr(d);
        // day: positions 4 and 5, space-padded on the left if <10
        const BuildNumberType day = (d[4] == ' ' ? 0 : d[4] - '0') * 10u + (d[5] - '0');
        // year: positions 7..10
        const BuildNumberType year = (d[7] - '0') * 1000u + (d[8] - '0') * 100u
            + (d[9] - '0') * 10u + (d[10] - '0');

        // days in past whole years since 2000
        const BuildNumberType yrs = year - 2000u;
        BuildNumberType days = yrs * 365u + LeapDaysSinceMillenium(year);

        // add months in this year
#pragma warning(disable: 6285)
        bool is_leap = (((year % 4u == 0) && (year % 100u != 0)) || (year % 400u == 0));
        for (int m = 1; m < month; ++m) {
            days += kDays[m];
            if (m == 2 && is_leap) days += 1;
        }

        // add days in this month
        days += day;

        return static_cast<BuildNumberType>(days);
    }

    // Parse two-digit number at ptr[0..1]
    consteval BuildNumberType TwoDigit(const char* ptr) {
        return (ptr[0] - '0') * 10u + (ptr[1] - '0');
    }

    // __TIME__ is "hh:mm:ss"
    consteval BuildNumberType SecondsSinceMidnight() {
        constexpr char const* t = __TIME__;
        const BuildNumberType hh = TwoDigit(t + 0);
        const BuildNumberType mm = TwoDigit(t + 3);
        const BuildNumberType ss = TwoDigit(t + 6);
        return static_cast<BuildNumberType>(hh * 3600 + mm * 60 + ss);
    }

    consteval BuildNumberType Compute() {
        return ComputeDays() * 86400u + SecondsSinceMidnight();
    }
}

static constexpr GGE::BuildNumberType kBuildIndex = GGE::BuildIndexDetails::Compute();

GGE::BuildInfo GGE::GetBuildInfo() noexcept
{
    return {
        kMajorBuildVersion,
        kMinorBuildVersion,
        kBuildIndex
    };
}
