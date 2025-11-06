# Pre-Publication Checklist

Voordat je deze repository publiceert op GitHub, doorloop deze checklist:

## ✅ Code en Build

- [x] Python bindings werken lokaal
- [x] CMake build systeem is geconfigureerd
- [x] setup.py installeert correct met `pip install .`
- [ ] Test op een schone Python environment
- [ ] Test op een ander systeem (optioneel maar aanbevolen)

## ✅ Documentatie

- [x] README.md is compleet met Python en C++ voorbeelden
- [x] INSTALL.md heeft instructies voor Ubuntu/macOS/Windows
- [x] CREDITS.md erkent originele auteurs
- [x] CONTRIBUTING.md is aanwezig
- [x] Examples folder heeft README
- [ ] Vervang alle `YOUR_USERNAME` placeholders met je GitHub username

## ⚠️ Te Vervangen Placeholders

Zoek en vervang in deze bestanden:

```bash
# Zoek naar placeholders
grep -r "YOUR_USERNAME" .

# Bestanden met placeholders:
# - README.md
# - INSTALL.md
# - setup.py
# - pyproject.toml
# - LOCAL_INSTALL.md
```

Vervang `YOUR_USERNAME` met je GitHub username.

## 📝 Optionele Aanpassingen

### setup.py
```python
maintainer='Arthur',  # Vervang met je naam
```

### pyproject.toml
```toml
maintainers = [
    {name = "Arthur"},  # Vervang met je naam/email
]
```

### CREDITS.md
```markdown
**Python Bindings Contributors:**
- Arthur (initial implementation)  # Vervang met je naam
```

## 🧹 Opschonen Voordat je Commit

```bash
# Verwijder build artifacts
rm -rf build/ *.egg-info/ dist/ .eggs/

# Verwijder Python cache
find . -type d -name __pycache__ -exec rm -rf {} +
find . -type f -name "*.pyc" -delete

# Verwijder virtual environment (optioneel)
rm -rf .venv/
```

## 📤 GitHub Repository Setup

1. **Maak een nieuwe repository op GitHub**
   - Naam: `eyerec` of `eyerec-python`
   - Beschrijving: "Python bindings for eyerec - Real-time pupil detection and tracking"
   - Public of Private (jouw keuze)
   - **Geen** README, license, of gitignore toevoegen (je hebt ze al)

2. **Link je lokale repo**
   ```bash
   cd /home/arthur/Projects/eyerec
   git remote add origin https://github.com/YOUR_USERNAME/eyerec.git
   # Of als je al een origin hebt:
   git remote set-url origin https://github.com/YOUR_USERNAME/eyerec.git
   ```

3. **Eerste commit en push**
   ```bash
   git add .
   git commit -m "Add Python bindings via pybind11"
   git push -u origin master
   ```

## 🎯 Na Publicatie

- [ ] Test installatie van GitHub: `pip install git+https://github.com/YOUR_USERNAME/eyerec.git`
- [ ] Update placeholders in documentatie met werkelijke URLs
- [ ] Voeg GitHub Topics toe: `eye-tracking`, `pupil-detection`, `opencv`, `python`, `pybind11`
- [ ] Overweeg een release tag te maken: `v0.1.0`

## 📧 Optioneel: Informeer Originele Auteurs

Als je wilt, kun je Thiago Santini informeren over je Python bindings:
- Open een issue in het originele repo
- Vermeld dat je Python bindings hebt toegevoegd
- Link naar je fork
- Vraag of ze interesse hebben om het te linken

## ✨ Klaar!

Na deze checklist is je repository klaar voor publicatie!

## Test Commando's

```bash
# Test lokale installatie
pip install .

# Test import
python -c "import pyeyerec; print(pyeyerec.PuRe().description())"

# Test voorbeeld
python examples/track_pupil.py purest /path/to/video.mp4

# Test vanaf GitHub (NA publicatie)
pip install git+https://github.com/YOUR_USERNAME/eyerec.git
```
