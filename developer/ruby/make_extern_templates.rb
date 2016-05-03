Dir.glob("model/**/*.hpp").each do |path|
  new_lines = []
  puts path
  contents = File.read(path).split("\n")
  contents.each_index do |i|
    line = contents[i]
    md = /^(\s*)typedef(\s*)([^\s]*)<([^\s]*)>(\s*)([^\s]*);(.*)$/.match(line)
    if md
      if /std::pair/.match(md[3])
        new_lines << "extern template struct #{md[3]}<openstudio::model::#{md[4]}>;"
      elsif /std::vector/.match(md[3])
        new_lines << "template<> std::vector<openstudio::model::#{md[4]}>::vector(size_type) = delete; // do not instantiate"
        new_lines << "template<> void std::vector<openstudio::model::#{md[4]}>::resize(size_type) = delete; // do not instantiate"
        new_lines << "extern template class #{md[3]}<openstudio::model::#{md[4]}>;"
      elsif /boost::optional/.match(md[3])
        new_lines << "extern template class #{md[3]}<openstudio::model::#{md[4]}>;"
      elsif /std::shared_ptr/.match(md[3])
        new_lines << "extern template class #{md[3]}<openstudio::model::detail::#{md[4]}>;"        
      end
    end
  end
  
  if new_lines.size > 0
    new_lines << ''
    
    index = 0
    contents.each_index do |i| 
      if /\#endif/.match(contents[i])
        index = i
      end
    end
    contents.insert(index, new_lines)
      
    File.open(path, 'w') do |file|      
      file << contents.join("\n") + "\n"
    end
    
    path = path.gsub('_Impl','').gsub('.hpp', '.cpp')
    if File.exist?(path)
      new_lines.reject! {|line| !/extern/.match(line)}
      new_lines.each {|line| line.gsub!('extern ', '')}
      
      contents = File.read(path).split("\n")
      index = 0
      contents.each_index do |i| 
        if /namespace openstudio/.match(contents[i])
          index = i 
          break
        end
      end
      contents.insert(index, new_lines)
      
      File.open(path, 'w') do |file|      
        file << contents.join("\n") + "\n"
      end  
      
    end
    
  end
  
end


# explicitly instantiate class (e.g. vector) for type without default constructor (deleted or just private?)