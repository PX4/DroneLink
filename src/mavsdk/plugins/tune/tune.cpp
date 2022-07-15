// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/tune/tune.proto)

#include <iomanip>
#include <mutex>

#include "tune_impl.h"
#include "plugins/tune/tune.h"

namespace mavsdk {

using TuneDescription = Tune::TuneDescription;

Tune::Tune(System& system) : PluginBase(), _impl{std::make_unique<TuneImpl>(system)} {}

Tune::Tune(std::shared_ptr<System> system) : PluginBase(), _impl{std::make_unique<TuneImpl>(system)}
{}

Tune::~Tune() {}

void Tune::play_tune_async(TuneDescription tune_description, const ResultCallback callback)
{
    _impl->play_tune_async(tune_description, callback);
}

Tune::Result Tune::play_tune(TuneDescription tune_description) const
{
    return _impl->play_tune(tune_description);
}

bool operator==(const Tune::TuneDescription& lhs, const Tune::TuneDescription& rhs)
{
    return (rhs.song_elements == lhs.song_elements) && (rhs.tempo == lhs.tempo);
}

std::ostream& operator<<(std::ostream& str, Tune::TuneDescription const& tune_description)
{
    str << std::setprecision(15);
    str << "tune_description:" << '\n' << "{\n";
    str << "    song_elements: [";
    for (auto it = tune_description.song_elements.begin();
         it != tune_description.song_elements.end();
         ++it) {
        str << *it;
        str << (it + 1 != tune_description.song_elements.end() ? ", " : "]\n");
    }
    str << "    tempo: " << tune_description.tempo << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, Tune::Result const& result)
{
    switch (result) {
        case Tune::Result::Unknown:
            return str << "Unknown";
        case Tune::Result::Success:
            return str << "Success";
        case Tune::Result::InvalidTempo:
            return str << "Invalid Tempo";
        case Tune::Result::TuneTooLong:
            return str << "Tune Too Long";
        case Tune::Result::Error:
            return str << "Error";
        case Tune::Result::NoSystem:
            return str << "No System";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, Tune::SongElement const& song_element)
{
    switch (song_element) {
        case Tune::SongElement::StyleLegato:
            return str << "Style Legato";
        case Tune::SongElement::StyleNormal:
            return str << "Style Normal";
        case Tune::SongElement::StyleStaccato:
            return str << "Style Staccato";
        case Tune::SongElement::Duration1:
            return str << "Duration 1";
        case Tune::SongElement::Duration2:
            return str << "Duration 2";
        case Tune::SongElement::Duration4:
            return str << "Duration 4";
        case Tune::SongElement::Duration8:
            return str << "Duration 8";
        case Tune::SongElement::Duration16:
            return str << "Duration 16";
        case Tune::SongElement::Duration32:
            return str << "Duration 32";
        case Tune::SongElement::NoteA:
            return str << "Note A";
        case Tune::SongElement::NoteB:
            return str << "Note B";
        case Tune::SongElement::NoteC:
            return str << "Note C";
        case Tune::SongElement::NoteD:
            return str << "Note D";
        case Tune::SongElement::NoteE:
            return str << "Note E";
        case Tune::SongElement::NoteF:
            return str << "Note F";
        case Tune::SongElement::NoteG:
            return str << "Note G";
        case Tune::SongElement::NotePause:
            return str << "Note Pause";
        case Tune::SongElement::Sharp:
            return str << "Sharp";
        case Tune::SongElement::Flat:
            return str << "Flat";
        case Tune::SongElement::OctaveUp:
            return str << "Octave Up";
        case Tune::SongElement::OctaveDown:
            return str << "Octave Down";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk